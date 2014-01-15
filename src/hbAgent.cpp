#include<iostream>
#include<zookeeper/zookeeper.h>
#include<boost/algorithm/string.hpp>
#include "hbAgent.h"
#include "json/json.h"
#include "MongoUUID.h"
#include "util/stringlib.h"
#include "utils/GString.h"
HBAgent::HBAgent(string const& serverHostnamelist,string const &zookeeperAddress){
	this->zookeeperAddress=zookeeperAddress;
	currentServer=-1;
	serverHostname.clear();
	stringstream ss;
	if(serverHostnamelist[serverHostnamelist.length()-1]!=','){
		ss<<serverHostnamelist<<",";
	}else{
		ss<<serverHostnamelist;
	}
	serverHostname=split(ss.str(),',');
	for(unsigned i=0;i<serverHostname.size();i++){
		cout<<"Add Server: "<<serverHostname[i]<<endl;
	}
	c=NULL;
}
void watcher(zhandle_t *zzh, int type, int state, const char *path,void *watcherCtx) {
	if(type==ZOO_SESSION_EVENT){
		*(bool*)watcherCtx=true;
	}
	return;
}
Error_Info HBAgent::readZookeeper(){
          Error_Info err; 
	  string zk_snap;
	  const string ZK_SNAP="/wde/gbase/data/snapshot";
          zhandle_t * zh;
	  bool pingpong=false;
          zh=zookeeper_init(zookeeperAddress.c_str(),watcher, 10000, 0, &pingpong, 0);                              
          char buffer[8192];
          int buflen=sizeof(buffer);
          struct Stat stat;
 	  if(zh){
 	  	int rc;
		int sleeptimes=0;
		while(!pingpong){
			sleep(1);
			sleeptimes++;
			if(sleeptimes==10){
				err.code=-2;
				err.description="Can't Connected to Zookeeper: "+zookeeperAddress;
				return err;
			}
		}
		if(zoo_state(zh)!=ZOO_CONNECTED_STATE){
			err.code=HB_READZOOKEEPER_FAIL; 			err.description="Can't Connected to Zookeeper: "+zookeeperAddress;


			return err;
		}
          	rc=zoo_get(zh,ZK_SNAP.c_str(),0,buffer,&buflen,&stat);
		if(rc==ZOK){
          		zk_snap=string(buffer,buflen);
		}else{
			err.code=HB_BADZOOKEEPER_CONFIG;
			err.description="get snapshot from zookeeper fail";
			return err;
		}
          }else{
	      err.code=HB_READZOOKEEPER_FAIL;
              err.description="zookeeper init fail";
	      return err;
          }
          zookeeper_close(zh);
	  boost::replace_all(zk_snap,"\'","\"");
	  Json::Value root;
	  Json::Reader reader;
	  bool parseSuccess=reader.parse(zk_snap,root);
	  if(!parseSuccess){
		err.code=HB_READZOOKEEPER_FAIL;
		err.description="Bad Zookpeer Value for snapshot in Zookeeper";
	  }
	  collection=root["name"].asString();
	  columnfamily="contents";
	  err.code=HB_OK;
	  err.description="zookeeper init success";
	  return err;
}           

Error_Info HBAgent::Init(){
	Error_Info errInfo=conn();
	cout<<errInfo.description<<endl;
	if(errInfo.code!=0){
		return errInfo;
	}else{
		errInfo=readZookeeper();
	}
	return errInfo;
}
Error_Info HBAgent::conn(){
	Error_Info errInfo;
	unsigned int next=(currentServer+1)%serverHostname.size();
	for(unsigned int i=0;i<serverHostname.size();i++){ 
		try{
			if(c){
				delete c;
				c=NULL;
			}
			string::size_type comma=serverHostname[next].find_first_of(":");
			string host=serverHostname[next].substr(0,comma);
			int port=atoi(serverHostname[next].substr(comma+1).c_str());
  			boost::shared_ptr<TSocket> socket(new TSocket(host,port));
			int timeout=1000*10;//default 10seconds
                	socket->setRecvTimeout(timeout);
                	socket->setSendTimeout(timeout);
  			boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  			boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
			c=new HbaseClient(protocol);
			transport->open();
			currentServer=next;
			cout<<"Connected to HBase Thrift Server: "<<serverHostname[currentServer]<<endl;
			errInfo.code=0;
			errInfo.description="HBase Thrift Server Connection Established";		      
			return errInfo;
		}
		catch(exception e){
			next++;
			next%=serverHostname.size();
		}
	}
	errInfo.code=HB_CONN_FAIL;
	errInfo.description="Couldn't Connect to HBase Thrift server";
	return errInfo;
}
Error_Info HBAgent:: Destroy(){
	Error_Info errInfo;
	errInfo.code=0;
	errInfo.description="Destroy HBase Agent Successfully!";
	if(c){
		delete c;
		c=NULL;
	}
	cout<<errInfo.description<<endl;
	return errInfo;
}
Error_Info HBAgent:: Put(GatherDoc const & gd){
	Error_Info errInfo;
    	vector<Mutation> mutations;
	{
    	mutations.push_back(Mutation());
    	mutations.back().column = columnfamily+":md5";
    	mutations.back().value  = gd.md5;
	}
	{
    	mutations.push_back(Mutation());
    	mutations.back().column = columnfamily+":ss";
    	mutations.back().value  = gd.snapshot;
	}
	{
    	mutations.push_back(Mutation());
    	mutations.back().column = columnfamily+":appid";
    	mutations.back().value  = gd.new_appid|gd.old_appid;
	}
	map<string,string> amap;
	int tryTimes=5;
	while(tryTimes--){
		try{
			string rowkey=ict::wde::gbasedata::reverseUrl(gd.url);
			
    			c->mutateRow(collection,rowkey,mutations,amap); 
			errInfo.code=0;
			errInfo.description="Insert an Snapshot Successfully!";
			return errInfo;
		}catch(IOError e){
			errInfo.code=HB_IO_HBASE;
			errInfo.description="HBase Service cannot accept this document: "+gd.url;
			cout<<errInfo.description<<endl;
			return errInfo;
		}catch(IllegalArgument e){
			errInfo.code=HB_INVAID_ARGS;
			errInfo.description="Illegal Argument: "+gd.url;
			cout<<errInfo.description<<endl;
			return errInfo;
		}
		catch(TException e){
			cout<<e.what()<<endl;
			errInfo=conn();
			if(errInfo.code!=0){
				cout<<errInfo.description<<endl;
				return errInfo;
			}
		}
	}
	errInfo.code=HB_IO_HBASE;
	errInfo.description="Could not write doc to HBase";
	return errInfo;	
}
