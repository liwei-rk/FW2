#include<iostream>
#include "ctAgent.h"
#include "util/inet.h"
#include "json/json.h"
using namespace std;
/* 
 * constructor
 */
Error_Info CTAgent::CTErrorCovert(CacheTube::Error_Info tmpErrInfo){
	Error_Info errInfo;
	{
		errInfo.code=tmpErrInfo.code;
		errInfo.description=tmpErrInfo.description;
	}
	return errInfo;
}
CTAgent::CTAgent(string topic,string backupDir)/*:parser(backupDir)*/{
	this->topic=topic;
	connected=false;
	setconfpath=false;
	lastError.code=0;
	lastError.description="This is the last error's descripiton,not useful,please ignore it";
	cancel=false;
}
bool CTAgent::isConnected(){
	return connected;
}
/*
 * use the Error_Info's Code to change the field 'connected' later
 * once the first Init failed,there maybe many cases:
 * 	1,ct is down			    2,or the configure is wrong
   we all believe the configure is wrong,so if the Init Failed,the Main	  process exit right now
 */
Error_Info CTAgent::Init(string const confpath){
	CacheTube:: Error_Info tmpErrInfo;
	/*
	 * we make it a pair,  new a CCacheTube,then Init right now
	 * it
	 */
	if(!setconfpath){
		this->confpath=confpath;
		setconfpath=true;
	}
	cacheTube=new CacheTube:: CCacheTube();
	tmpErrInfo=cacheTube->Init(confpath);
	if(tmpErrInfo.code==CacheTube::kErrCode_OK){
		connected=true;	
	}else{
		connected=false;
	}
	//pthread_create(&tid_ctsender,NULL,ctSender,this);
	//pthread_create(&tid_ctrsender,NULL,ctResender,this);
	return CTErrorCovert(tmpErrInfo);
}
Error_Info CTAgent:: Destroy(){
	CacheTube:: Error_Info tmpErrInfo;
	cancel=true;
	//gdb.Destroy();
	//pthread_join(tid_ctsender,0);
	//pthread_join(tid_ctrsender,0);
	tmpErrInfo=cacheTube->Destroy();
	if(tmpErrInfo.code==CacheTube::kErrCode_OK){
		tmpErrInfo.description="Destroy CacheTube Agent Successfully!";
	}else{
		tmpErrInfo.description="Destroy CacheTube Agent Failed!";
	}
	cout<<tmpErrInfo.description<<endl;
	delete cacheTube;
	return CTErrorCovert(tmpErrInfo);
}
/*
void* CTAgent::ctSender(void* args){
	cout<<"Start \"CacheTubeSender\" Thread to Send Messages"<<endl;
	CTAgent* cta=(CTAgent*)args;
	while(!cta->Cancel()){
		GatherDoc gd(cta->gdb.Pop());
		if(cta->gdb.exit){
			break;
		}
		cta->lastError=cta->Put(gd);
	}
	cout<<"End \"CacheTubeSender\" Thread"<<endl;
	return 0;
}
void* CTAgent::ctResender(void* args){
	cout<<"Start \"CacheTubeReSender\" Thread to Resend Messages"<<endl;
	CTAgent* cta=(CTAgent*)args;
	while(!cta->Cancel()){
		sleep(1);
	}
	cout<<"End \"CacheTubeResender\" Thread"<<endl;
	return 0;
}
*/

/*
 * when we call reInit,it means conneted==false,but we don't 
 * rely on it,just call Init again();
 * the reInit method is used for reconnect the CacheTube
 */
Error_Info CTAgent::reInit(){
	Error_Info errInfo;
	if(cacheTube){
		cacheTube->Destroy();
		delete cacheTube;
	}	
	errInfo=Init(confpath);
	if(errInfo.code==0){
		connected=true;	
	}else{
		connected=false;
	}
	return errInfo;
}
/*
 *Put will change "connected" state ,if inserting the ct failed
 */
Error_Info CTAgent:: Put(string const& queueName,CacheTube:: Message const& msg){
	CacheTube:: Error_Info tmpErrInfo;
	vector<CacheTube::Message> msgs;
	msgs.push_back(msg);
	tmpErrInfo=cacheTube->Put(queueName,msgs);
	if(tmpErrInfo.code==0){
	}else{
		tmpErrInfo.code=-1;
		connected=false;
	}
	return CTErrorCovert(tmpErrInfo);
}
Error_Info CTAgent:: Put(string const & docJson){
	CacheTube::Message msg=docJsonToMessage(docJson);
	return Put(topic,msg);
}
/*
Error_Info CTAgent::Putb(GatherDoc const& gd){
	gdb.Push(gd);
	return lastError;
}
*/
Error_Info CTAgent::Put(GatherDoc const& gd){
	string gdJson=GatherDocToJson(gd);
	return Put(gdJson);
}
string CTAgent::GatherDocToJson(GatherDoc const& gd){
	Json::Value root;
	Json::Value arrayPics;
	Json::Value arrayVideos;
	Json::Value arrayBoardClassTag;
	root["url"]		=gd.url;
	root["channel_id"]	=gd.channel_id;
	root["title"]		=gd.title;
	root["doc_abstract"]	=gd.doc_abstract;
        root["keywords"]	=gd.keywords;
        root["keyvect"]		=gd.keyvect;
	root["person_list"]	=gd.person_list;
	root["region_list"]	=gd.region_list;
	root["organ_list"]	=gd.organ_list;
	root["publish_time"]	=gd.publish_time;
	root["gather_time"]	=gd.gather_time;
	root["md5"]		=gd.md5;
	root["content_finger"]  =gd.content_finger;
	root["page_finger"]	=gd.page_finger;
	root["sentiment"]	=gd.sentiment;
	root["author"]		=gd.author;
	root["click_count"]	=gd.click_count;
	root["reply_count"]	=gd.reply_count;
	root["is_site_homepage"]=gd.is_site_homepage;
	root["evidence_degree"]	=gd.evidence_degree;
	root["importance_degree"]=gd.importance_degree;
	root["board_id"]	=gd.board_id;
	root["board_name"]	=gd.board_name;
	root["site_id"]		=gd.site_id;
	root["site_name"]	=gd.site_name;
	root["old_appid"]	=(Json::Int64)gd.old_appid;
	root["new_appid"]	=(Json::Int64)gd.new_appid;
	//root["appid"]		=(Json::Int64)(gd.appid);
	//root["board_class_id"]	=gd.board_class_id;
	//root["board_class_name"] =gd.board_class_name;
	for(vector<string>::size_type i=0;i<gd.pictures.size();i++){
		Json::Value item=gd.pictures[i];
		arrayPics.append(item);
	}
	for(vector<string>::size_type i=0;i<gd.videos.size();i++){
		Json::Value item=gd.videos[i];
		arrayVideos.append(item);
	}
	for(vector<string>::size_type i=0;i<gd.board_class_tag.size();i++){
		Json::Value item=gd.board_class_tag[i];
		arrayBoardClassTag.append(item);
	}
	root["pictures"]	=arrayPics;
	root["videos"]      	=arrayVideos;
	root["board_class_tag"] =arrayBoardClassTag;

	root["content"]		=gd.content;
	//snapshot不必传入CacheTube
	//root["snapshot"]	=gd.snapshot;
	root["old_doc"]		=gd.old_doc;
	//root["floor_num"]	=gd.floor_num;
	root["language"]	=gd.language;
	return root.toStyledString();
}
CacheTube::Message CTAgent::docJsonToMessage(string const &docJson){
	CacheTube::Message msg;
	{
	msg.queue_name=topic;
	msg.srcip=ip_search();
	msg.content=docJson;
	}
	return msg;
}
/*
 * for extention and test
 */
Error_Info CTAgent:: Get(string const& queueName,vector<CacheTube:: Message> & msgs){
	CacheTube:: Error_Info tmpErrInfo;
	tmpErrInfo=cacheTube->Get(queueName,msgs);
	return CTErrorCovert(tmpErrInfo);
}
