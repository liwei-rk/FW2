#include <fstream>
#include <sstream>
#include <map>
#include "WriteDoc.h"
#include "json/json.h"
#include "ctAgent.h"
#include "mgAgent.h"
#include "hbAgent.h"
#include "util/stringtrim.h"
namespace WriteDoc{
static bool snapshotToMongo=false;
static bool snapshotToHBase=false;
string HBaseThriftServer="localhost:9091";
string ZookeeperAddress="snapshot";
enum WriteDocErrorCode{
	WD_OK=0x0,
	//start from 0x100;
	WD_BAD_CONFIG_FILE=0x100,
	WD_INIT_FAILED=0x101,
	WD_CLOSE_FAILED=0x102

};
class lwVampirelog{
  public:
	time_t lastlogtime;
	int cterror;
	int ctsuccess;
	int mgerror;
	int mgsuccess;
	ofstream logfile;
	lwVampirelog(){
		reset();
	}
	void Init(){
	}
	void Close(){
		//logfile.close();
	}
	void reset(){
		lastlogtime=time(0);
		cterror=0;
		ctsuccess=0;
		mgerror=0;
		mgsuccess=0;
	}
	void logError(Error_Info& errInfo){
		stringstream loginfo;
		if(errInfo.code!=0){
			loginfo<<"Error Code:"<<errInfo.code<<" Error description: "<<errInfo.description;
		}else{
			loginfo<<"Success: "<<errInfo.description<<endl;
		}
		logtofile(loginfo.str());
	}
	void log(Error_Info cterrInfo,Error_Info mgerrInfo){
		if(cterrInfo.code==0){
			ctsuccess++;
		}else{
			cterror++;
			logError(cterrInfo);
		}
		if(mgerrInfo.code==0){
			mgsuccess++;
		}else{
			mgerror++;
			logError(mgerrInfo);
		}
		time_t now=time(0);
		if((now-lastlogtime)>=30){
			stringstream loginfo;
			loginfo<<"Statics: Cachetube: "<<ctsuccess<<" success "<<cterror<<" fail ; "<<"Snapshot(Mongo): "<<mgsuccess<<" success "<<mgerror<<" fail "<<"during the last 30 seconds"<<endl;
			logtofile(loginfo.str());
			reset();
		}
	}
	void logtofile(string loginfo){
		time_t tm=time(0);
		struct tm * timeinfo;
		timeinfo=localtime(&tm);
		string time=asctime(timeinfo);
		time[time.length()-1]=' ';
		stringstream errinfo;
		errinfo<<"["<<time<<" INFO]"<<"[writedoc]"<<" ";
		errinfo<<loginfo;
		cout<<errinfo.str()<<endl;
	}
};
static lwVampirelog AlwVampirelog;
Error_Info::Error_Info(int code):description("ok"){
	this->code=code;
}
GatherDoc::GatherDoc(int appid){
		url="";
		channel_id=0;//?
		title="";
		doc_abstract="";
		keywords="";
		keyvect="";
		person_list="";
		region_list="";
		organ_list="";
		publish_time=0;//resolved:
		gather_time=0;//
		md5="";
		content_finger="";
		page_finger="";
		sentiment=0;
		author="";
		click_count=0;
		reply_count=0;
		is_site_homepage=0;
		evidence_degree=0;
		importance_degree=0;
		board_id=0;
		board_name="";
		site_id=0;
		site_name="";
		pictures= vector<string>(1,"");
		videos= vector<string>(1,"");
		content="";
		snapshot="";
		old_doc=0;
		language=0;
		//this->appid=0;
		old_appid=new_appid=0;
		board_class_tag=vector<string>(1,"");	
}
CWriteDoc::CWriteDoc(){
	m_mgAgent=NULL;
	m_ctAgent=NULL;
	m_hbAgent=NULL;
	m_mongoServerHostname="172.22.0.37:6080";
	m_mongoDBname="liwei";
	m_mongoCollectionName="ljh";
	m_queueName="topic_liwei";
}
bool CWriteDoc::LoadConfigFile(string const configfile){
	ifstream conf(configfile.c_str());	
	if(!conf){
		return false;
	}
	size_t found;
	string line;
	map<string,string> confmap;
	map<string,string>::iterator it;
	/*
	 * 空行，注释全部过滤
	 */
	while(getline(conf,line)){
		if(line==""){
			continue;
		}
		/*
		 *trim the line ,that is there is no blank symbol in the line;
		 */
		line=trim(line);		
		found=line.find_first_of('#');
		/*
		 *remove comment lines,which start with "#"
		 */
		if((found!=string::npos)&&(found==0)){
			continue;
		}
		/*
		 *other wise the line maybe contain configure information
		 *which like the format key=value;
		 */
		found=line.find_first_of('=');
		if((found==string::npos)||(found==(line.size()-1))){
			continue;
		}else{
		 /*
		  *put the key value in the map
		  */
			string key=line.substr(0,found);
			string value=line.substr(found+1,line.size()-1);
			pair<map<string,string>::iterator,bool> ret;
			ret=confmap.insert(map<string,string>::value_type(key,value));
			if(!ret.second){
				cout<<"fatal error ,exit"<<endl;
				return false;
			}
		 }
	}
	/*	
	 *set the field
         *		m_mongoServerHostname
	 *		m_mongoDBname
	 *		m_mongoCollectionName
	 *		m_queueName
	 *	fields; 
	 */
	{
		it=confmap.find("server_list");
		if(it!=confmap.end()){
		//	ToDo		
			cout<<"Configure Cachetube Agent : "<<it->second<<endl;
		}
		it=confmap.find("queue_name");
		if(it!=confmap.end()){
			m_queueName=it->second;
			cout<<"Configure Queue: "<<it->second<<endl;
		}
		it=confmap.find("mongo_server_address");
		if(it!=confmap.end()){
			m_mongoServerHostname=it->second;
			cout<<"Configure Mongo Server: "<<it->second<<endl;
		}
		it=confmap.find("mongo_db_name");
		if(it!=confmap.end()){
			m_mongoDBname=it->second;
			cout<<"Configure Mongo DB Name: "<<it->second<<endl;
		}
		it=confmap.find("mongo_collection_name");
		if(it!=confmap.end()){
			m_mongoCollectionName=it->second;
			cout<<"Configure Mongo Collection Name: "<<it->second<<endl;
		}
		it=confmap.find("hbase_thrift_server_address");
		if(it!=confmap.end()){
			HBaseThriftServer=it->second;
			cout<<"Configure HBaseThriftServer: "<<it->second<<endl;
		}
		it=confmap.find("zookeeper_server_address");
		if(it!=confmap.end()){
			ZookeeperAddress=it->second;
			cout<<"Configure Zookeeper Server Address: "<<it->second<<endl;
		}
		it=confmap.find("snapshotToMongo");
		if(it!=confmap.end()){
			snapshotToMongo=(it->second)=="on"?true:false;
			cout<<"Configure SnapshotToMongo : "<<it->second<<endl;
		}
		it=confmap.find("snapshotToHBase");
		if(it!=confmap.end()){
			snapshotToHBase=(it->second)=="on"?true:false;
			cout<<"Configure SnapshotToHBase: "<<it->second<<endl;
		}
	}
	return true;
}
CWriteDoc::~CWriteDoc(){
}
Error_Info CWriteDoc::Init(string configfile_path){
	AlwVampirelog.Init();
	bool initfailed=false;
	Error_Info errInfo;
	if(!LoadConfigFile(configfile_path)){
		errInfo.code=WD_BAD_CONFIG_FILE;
		errInfo.description="Loadconfigfile fail";
		initfailed=true;
		AlwVampirelog.logError(errInfo);
	}
	cout<<"Begin Init CacheTube Agent"<<endl;
	m_ctAgent=new CTAgent(m_queueName,"CachetubeBackup");
	errInfo=((CTAgent *)m_ctAgent)->Init(configfile_path);
	if((errInfo.code!=0)){
		AlwVampirelog.logError(errInfo);
		initfailed=true;
		cout<<"Init CacheTube Agent Failed! Because:"<<errInfo.description<<endl;
	}else{
		cout<<"Init CacheTube Agent Successfully!"<<endl;
	}
	if(snapshotToMongo){
		cout<<"Begin Init Mongodb Agent"<<endl;
		m_mgAgent=new MGAgent(m_mongoServerHostname,m_mongoDBname,m_mongoCollectionName,"MongoBackup");
		errInfo=((MGAgent *)m_mgAgent)->Init();
		if((errInfo.code!=0)){
			AlwVampirelog.logError(errInfo);
			initfailed=true;
			cout<<"Init Mongodb Agent failed! Because:"<<errInfo.description<<endl;
		}else{
			cout<<"Init Mongodb Agent Successfully!"<<endl;
		}
	}
	if(snapshotToHBase){
		cout<<"Begin Init HBase Agent"<<endl;
		m_hbAgent=new HBAgent(HBaseThriftServer,ZookeeperAddress);
		errInfo=((HBAgent *)m_hbAgent)->Init();
		if((errInfo.code!=0)){
			AlwVampirelog.logError(errInfo);
			initfailed=true;
			cout<<"Init HBase Agent failed! Because:"<<errInfo.description<<endl;
		}else{
			cout<<"Init HBase Agent Successfully!"<<endl;
		}
	}
	if(initfailed){
		errInfo.code=WD_INIT_FAILED;
		errInfo.description="Init Writedoc Interface Failed";
		AlwVampirelog.logError(errInfo);
	}
	return errInfo;
}
Error_Info CWriteDoc::Close(){
	Error_Info errInfo;
	bool closefailed=false;
	if(m_ctAgent){
		errInfo=((CTAgent*)m_ctAgent)->Destroy();
		delete (CTAgent*)m_ctAgent;
		m_ctAgent=NULL;
		if(errInfo.code!=0){
			AlwVampirelog.logError(errInfo);
			closefailed=true;
		}
	}
	if(m_mgAgent){
		errInfo=((MGAgent*)m_mgAgent)->Destroy();
		delete (MGAgent*)m_mgAgent;
		m_mgAgent=NULL;
		if(errInfo.code!=0){
			AlwVampirelog.logError(errInfo);
			closefailed=true;
		}
	}
	if(m_hbAgent){
		errInfo=((HBAgent*)m_hbAgent)->Destroy();
		delete (HBAgent*)m_hbAgent;
		m_hbAgent=NULL;
		if(errInfo.code!=0){
			AlwVampirelog.logError(errInfo);
			closefailed=true;
		}
	}
	if(closefailed){
		errInfo.code=WD_CLOSE_FAILED;
		errInfo.description="Close WriteDoc Interface Failed!";
	}else{
		errInfo.code=WD_OK;
		errInfo.description="Destroy WriteDoc Interface Successfully!";
	}
	AlwVampirelog.logError(errInfo);
	AlwVampirelog.Close();
	return errInfo;
}
Error_Info CWriteDoc::Write(GatherDoc&	gd){
	Error_Info cterrInfo=WriteToCacheTube(gd);
	Error_Info snapshotErrInfo;
	snapshotErrInfo=WriteSnapshot(gd);
	AlwVampirelog.log(cterrInfo,snapshotErrInfo);
	return (cterrInfo.code==0)?snapshotErrInfo:cterrInfo;
}
Error_Info CWriteDoc::WriteSnapshot(GatherDoc& gd){
	Error_Info err,err_mongo,err_hbase;
	if(snapshotToMongo){
		err_mongo=((MGAgent*)m_mgAgent)->Put(gd);
	}
	if(snapshotToHBase){
		err_hbase=((HBAgent*)m_hbAgent)->Put(gd);
	}
	if((err_mongo.code==0)&&(err_hbase.code==0)){
		err.code=0;
		err.description="Write Snapshot Success";
	}else{
		err=((err_mongo.code==0)?err_hbase:err_mongo);
	}
	return err;
}
Error_Info CWriteDoc::WriteToCacheTube(GatherDoc& gd){
	return ((CTAgent *)m_ctAgent)->Put(gd);
}
}
