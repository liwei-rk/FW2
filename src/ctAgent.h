#ifndef CTAGENT_H
#define CTAGENT_H
/*
 *ct Agent is used for monitor cacheTube,contain the connection of ct,and insert  document to ct;
 */
#include <fstream>
#include<pthread.h>
#include "WriteDoc.h"
#include "CacheTube.h"
//#include "GDBuffer.h"
//#include "parser.h"
using namespace std;
using namespace WriteDoc;
class CTAgent{
	public:
		/*may be we should use thread-safe method 
                 *
                 */
		bool connected;
		//wether we should lock the resending and connected;
		string topic;
		bool setconfpath;
		string confpath;
		CacheTube::CCacheTube* cacheTube;
		//GDBuffer gdb;
		//pthread_t tid_ctsender;
		//pthread_t tid_ctrsender;
		Error_Info lastError;
		bool cancel;
		//Parser parser;
	public:
		CTAgent(string topic,string backupDir);
		bool isConnected();
		string getConfpath(){return confpath;}
		string getTopic(){return topic;}
		Error_Info Init(string const confpath);
		Error_Info reInit();
		Error_Info Put(string const& queueName,CacheTube:: Message const& msg);
		//Error_Info Put(t& queueName,CacheTube:: Message const & msg);
		Error_Info Put(string const & docJson);
		Error_Info Put(GatherDoc const& gd);
		//Error_Info Putb(GatherDoc const& gd);
		string GatherDocToJson(GatherDoc const& gd);
		static void* ctSender(void* args);
		static void* ctResender(void* args);
		bool Cancel(){return cancel;}
		/*
 		 *PutS means we can almostly insert a JsonDoc successfully		
		 */
		Error_Info Get(string const& queueName,vector<CacheTube:: Message> & msg);
		Error_Info Destroy();
		Error_Info CTErrorCovert(CacheTube::Error_Info tmpErrInfo);
		CacheTube::Message docJsonToMessage(string const &docJson);
};
#endif //CTAGENT_H
