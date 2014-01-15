#ifndef WRITEDOC_H
#define WRITEDOC_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
namespace WriteDoc {
using namespace std;
/*GatherDoc 结构体定义
 */
typedef struct GatherDoc 
	{ 
		string url;	//文章url
		int channel_id; //通道类型id
		string title; //文章标题
		string doc_abstract; //文章摘要
		string keywords;//关键词
		string keyvect; //文章关键词向量，格式：(w1)[n1];(w2)[n2];....
		string person_list; //文章出现人名列表，格式：(w1)[n1];(w2)[n2];....
		string region_list; //文章出现地名列表，格式：(w1)[n1];(w2)[n2];....
		string organ_list; //文章出现机构名列表，格式：(w1)[n1];(w2)[n2];....
		int publish_time; //文章发布时间，时间戳
		int gather_time;
		string md5; //网页md5(一般由url生成)
		string content_finger; //文章内容指纹
		string page_finger; //文章翻页指纹(用于判断是否是同一篇文章的不同分页)
		int sentiment; //文章倾向性
		string author	; //文章作者（论坛、博客）				
		int click_count; //文章点击数
		int reply_count; //回复数		
		int is_site_homepage; //文章是否出现在首页0:否 1：是
		int evidence_degree; //版块可信度
		int importance_degree; //版块重要度
		int board_id; //板块id
		string board_name; //板块名称
		int site_id; //网站id
		string site_name; //网站名称
		//int board_class_id; //板块分类id
		//string board_class_name; //板块分类名称		
		vector<string> pictures; //文章出现图片url列表
		vector<string> videos;//文章出现视频url列表
		string content; //正文
		string snapshot; //快照
		int old_doc; //是否是已采入文章，用于标识论坛点击回复数的刷新采集。0:否 1:是
		//int floor_num; //.....
		int language;
		vector<string> board_class_tag;
		GatherDoc();
		/*
		void dump(GatherDoc const& gd);
		GatherDoc(GatherDoc const & gd);
		GatherDoc& operator=(GatherDoc const& gd);
		~GatherDoc(){}
		*/
	} GatherDoc;
	struct Error_Info { 
		size_t code; //返回错误码，0代表正常，其他为异常	
		string  description; //具体的错误信息，在异常时用于调试和日志
	};
	class CWriteDoc{
		public:
			CWriteDoc();
			~CWriteDoc();
			/*
			 *在使用Write方法之前需要调用Init()方法,返回Error_Info信息；
			 */
			Error_Info Init(string configfile_path="client.conf");   
			Error_Info Write(GatherDoc& gd);
			Error_Info Close();
		private:
			/*
			 *私有方法，调用者无需关心
			 *you don't need to care about these fields;
			 */
			Error_Info WriteSnapshot(GatherDoc& gd);
			Error_Info WriteToCacheTube(GatherDoc& gd);
			/*
	 		 *功能简介：用于把GatherDoc转化成相应的JSON字符串结构体
	 		 *@param GaterDoc gatherDoc
	 		 *@return Json格式的字符串
	 		 */
			string GatherDocToJson(GatherDoc &gatherDoc);
			string m_mongoServerHostname;	
			string m_mongoDBname;
			string m_mongoCollectionName;
			string m_queueName;
			void* m_mgAgent;
			void* m_ctAgent;
			bool Reconnect();
			bool GetSnapshot(GatherDoc& gd);
			bool Sanity(GatherDoc& gd);
			bool LoadConfigFile(string const configfile);
	};
}
#endif //end WRITEDOC_H
