#include<iostream>
#include "mgAgent.h"
#include "json/json.h"
#include "MongoUUID.h"
#include "util/stringlib.h"
Error_Info MGAgent::conn(){
	Error_Info errInfo;
	int failed_index=-1;
	//get failed connection index from serverHostnamelist
	if(c){
		//if c is not null,failed_index is in [0,size()-1]
		string failed_mongos=c->getServerAddress();
		cout<<"Mongo Server is unReachalbe "<<failed_mongos<<endl;
		for(unsigned int i=0;i<serverHostname.size();i++){
			if(serverHostname[i]==failed_mongos){
				failed_index=i;	
			}
		}
	}
	unsigned int next=(failed_index+1)%serverHostname.size();
	for(unsigned int i=0;i<serverHostname.size();i++){ 
		try{
			if(c){
				delete c;
			}
			c=new DBClientConnection();
			c->connect(serverHostname[next]);
			cout<<"Connect to Mongo : "<<c->getServerAddress()<<endl;
			errInfo.code=0;
			errInfo.description="Mongo Connection Established";		      
			return errInfo;
		}
		catch(DBException e){
			next++;
			next%=serverHostname.size();
		}
	}
	errInfo.code=MG_CONN_FAIL;
	errInfo.description="Connect Mongo Failed"; 
	return errInfo;
}
MGAgent::MGAgent(string const& serverHostnamelist,string const &db,string const &collection,string const& backupDir)/*:parser(backupDir)*/{
	this->serverHostnamelist=serverHostnamelist;
	this->db=db;
	this->collection=collection;
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
	ns=db+"."+collection;
	c=NULL;
}
/*
 * use the Error_Info's Code to change the field 'connected' later
 */
Error_Info MGAgent::Init(){
	//获得初始连接
	Error_Info errInfo=conn();
	cout<<errInfo.description<<endl;
	return errInfo;
}
Error_Info MGAgent:: Put(GatherDoc const & gd){
	
	Error_Info errInfo;
	BSONObjBuilder b;
	BSONObj bb;
	uint32_t ts=time(0);
	uint64_t uuid=gen_mongo_uuid(ts);
	b.append("url",gd.url);
	b.append("md5",gd.md5);
	b.append("appid",(long long)gd.new_appid|(long long)gd.old_appid);
	b.append("snapshot",gd.snapshot);
	b.append("it",ts);
	b.append("_id",(long long)uuid);
	bb=b.obj();
	int tryTimes=10;
	while(tryTimes--){
		try{
			if(!c){
				errInfo.code=MG_DEFAULT;
				errInfo.description="The libwritedoc.so may has some bug,please report";
				cout<<errInfo.description<<endl;
				return errInfo;
			}
			c->insert(ns,bb);
			errInfo.code=0;
			errInfo.description="Insert an Snapshot Successfully!";
			break;
		}catch(DBException e){
			errInfo=conn();
			if(errInfo.code!=0){
				return errInfo;
			}
		}
	}
	errInfo.code=MG_IO;
	errInfo.description="Couldn't put a document to Mongo";
	return errInfo;	
}
Error_Info MGAgent:: Destroy(){
	Error_Info errInfo;
	errInfo.code=0;
	errInfo.description="Destroy Mongo Agent Successfully!";
	if(c){
		delete c;
		c=NULL;
	}
	cout<<errInfo.description<<endl;
	return errInfo;
}
