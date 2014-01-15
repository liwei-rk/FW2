#include "../src/WriteDoc.h"
#include "CacheTube.h"
using namespace std;
using namespace WriteDoc;
using namespace CacheTube;
void testTask(CWriteDoc& wd){
	/*example
         *build a GatherDoc gd;初始化一个GatherDoc结构体，用于数据传输；
         */
	WriteDoc::Error_Info errInfo;
	long num=1;
	GatherDoc gd;
	{
		gd.url="https://www.baidu.com/root/liwei";
		gd.channel_id=1;
		gd.title="title";
		gd.doc_abstract="doc_abstract";
		gd.keywords="keywords";
		gd.keyvect="keyvect";
		gd.person_list="person_list";
		gd.region_list="region_list";
		gd.organ_list="orgon_list";
		gd.publish_time=0;
		gd.gather_time=11;
		gd.md5="md5";
		gd.content_finger="content_finger";
		gd.page_finger="page_finger";
		gd.sentiment=1;
		gd.author="author";
		gd.click_count=1;
		gd.reply_count=1;
		gd.is_site_homepage=1;
		gd.evidence_degree=1;
		gd.importance_degree=1;
		gd.board_id=100;
		gd.board_name="board_name";
		gd.site_id=1;
		gd.site_name="site_name";
	//	gd.board_class_id=1;
	//	gd.board_class_name="board_class_name";
		gd.pictures= vector<string>(10,"hello");
		gd.videos= vector<string>(10,"world");
		gd.content="content";
		gd.snapshot="snapshot";
		gd.old_doc=0;
	}	
	for(long i=0;i<num;i++){
		/*
 		 * 样例中只有url,md5 和channel_id 不同
  		 */
		stringstream tmp;
		tmp<<i;
		string tmpstr=tmp.str();
	{
		gd.url=string("http://www.baidu.com/home/liwei")+__TIME__;
		gd.channel_id=i;
		gd.title="title"+tmpstr;
		gd.doc_abstract="doc_abstract"+tmpstr;
		gd.keywords="keywords"+tmpstr;
		gd.keyvect="keyvect"+tmpstr;
		gd.person_list="person_list"+tmpstr;
		gd.region_list="region_list"+tmpstr;
		gd.organ_list="orgon_list"+tmpstr;
		gd.publish_time=i;
		gd.gather_time=13;
		gd.md5="md5"+tmpstr;
		gd.content_finger="content_finger"+tmpstr;
		gd.page_finger="page_finger"+tmpstr;
		gd.sentiment=i;
		gd.author="author"+tmpstr;
		gd.click_count=i;
		gd.reply_count=i;
		gd.is_site_homepage=i%2;
		gd.evidence_degree=i;
		gd.importance_degree=i;
		gd.board_id=i;
		gd.board_name="board_name"+tmpstr;
		gd.site_id=i;
		gd.site_name="site_name"+tmpstr;
		gd.pictures= vector<string>(10,"hello"+tmpstr);
		gd.videos= vector<string>(10,"world"+tmpstr);
		gd.content="content"+tmpstr;
		gd.snapshot="snapshot"+tmpstr;
		gd.old_doc=i%2;
		gd.language=10;
		gd.appid=101;
		gd.board_class_tag=vector<string>(10,"m2_1");
	}	
		errInfo=wd.Write(gd);
		if(errInfo.code!=0){
			cout<<"write gatherdoc failed"<<endl;
		}else{
			cout<<"write gatherdoc success"<<endl;
		}
		//sleep(10);
	}
	//errInfo=wd.Close();
}
int write_example(CCacheTube& cacheTube){
	/*
	 *Write messages to CacheTube have 4 steps
	 *First,construct a CCacheTube object named as cacheTube
	 *Second,before you use cacheTube,call cacheTube.Init(string configure,path)
	 *Third,to send Messages,call cacheTube.Put(string topic,vector<Message> messages)
         *Forth,before you exit call cacheTube.Close() to release the resourses
	 */

	//First,construct a CCacheTube object and an Error_Info object
	/*Error_Info class,which hold the information returned by CCacheTube's method
	 * struct Error_Info{
	 *	int32_t code;
	 *	string description;
	 * }
	 */

	//Second,call CCacheTube::Init(string configurepath)
	/*
	 *If the e_info.code==kErrCode_OK (defined in CacheTube.h),it means the init is sucessful,so we can continue;
	 *Otherwise,we must stop,because the CacheTube may in the wrong state;
	 */

	/*Third,call CCacheTube::Put(string topic,vector<Message>& v_msgs) to send the messages to the Server
         *the topic is the queue name,which the Messages  belong  to
	 *the v_msgs is a group of Message,so we can send a batch of Messages at once.
	 */
	string strTopic="yqpt_test";	//Topic means Queue_name
	/*
	 *To call the CCacheTube::Put,we have to bulid  vector<Message> 
	 */
	vector<Message> v_msgs;
	//v_msgs can have any number Messages between [1,100],the Example here we let the v_msgs have only one memeber
	Message msg; //The Message is defined in CacheTube.h
	//you have to set  four members of it
	//the ip of your machine
	msg.srcip = "221.0.111.130";
	//the time when the Message was created
	(void)time( &msg.created_time );
	//the JSON-Styled content you want to send
	msg.queue_name=strTopic;
	msg.content=
	"{\"si\":1000000003,\"sn\":\"sn\",\"mid\":\"m13b8ca702bd\",\"mt\":\"content\",\"cf\":\"cf\",\"ui\":\"13b8ca702bd\",\"un\":\"un\",\"scn\":\"scn\",\"iu\":\"iu\",\"mu\":\"mu\",\"srn\":\"srn\",\"vi\":\"vi\",\"rc\":0,\"cc\":0,\"pt\":0,\"gt\":0,\"nc\":[\"1\",\"2\"],\"ri\":\"ri\",\"rpi\":\"rpi\",\"ru\":\"ru\",\"irp\":0,\"rpm\":\"rpm\",\"rpu\":\"rpu\",\"rps\":\"rps\",\"srh\":\"srh\",\"om\":0,\"_id\":0,\"it\":0,\"ut\":0}";
	msg.content="{key1:value1,key2:value2}";
	v_msgs.push_back( msg );
	CacheTube::Error_Info e_info;
	cout<<v_msgs.size()<<endl;
	
	for(int lw=0;lw<2;lw++){
		e_info = cacheTube.Put(strTopic, v_msgs );

		if ( kErrCode_OK != e_info.code ) {
			cout<<" Put Error"<<endl;
		}else{
		cout<<" Put OK! "<<endl;
		}
	}
}
int read_example(CCacheTube& ct){
	vector<Message> v_msgs;
	ct.Get("yqpt_test",v_msgs);
	for(unsigned int i=0;i<v_msgs.size();i++){
		//std::cout<<v_msgs[i].content<<endl;
		cout<<i<<endl;
	}
	cout<<"size is "<<v_msgs.size()<<endl;
	
}
int main(){
	WriteDoc::Error_Info errInfo;
	WriteDoc::CWriteDoc wd;
	errInfo=wd.Init();
	if(errInfo.code!=0){
		cout<<errInfo.description<<endl;
	}
	CCacheTube cacheTube;
	CacheTube::Error_Info e_info;
	string strConfPath = "./client.conf";
	e_info = cacheTube.Init( strConfPath );
	if ( e_info.code!=kErrCode_OK ) {
		cout<<"CacheTube Init Failed, error code = "<<e_info.code<<" description = "<<e_info.description<<endl;
		return -1;
	}else{
		cout<<"use libcachetube.so Init OK! "<<endl;
	}
	for(int i=0;i<1;i++){
		cout<<"use libwritedoc.so"<<endl;
		testTask(wd);
		cout<<"use libcachetube.so"<<endl;
		write_example(cacheTube);
		sleep(1);
	}
	read_example(cacheTube);
	cacheTube.Destroy();
	cout<<"done"<<endl;
}
