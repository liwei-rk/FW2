#ifndef MGAGENT_H
#define MGAGENT_H
/*
 *mgAgent is used for monitor mongoDB,contain the connection of mongo,and insert  document to mongo;
 */
#include<pthread.h>
#include<vector>
/*
 * we inculde WriteDoc.h just used for the Error_Info structure
 */
#include "WriteDoc.h"
//#include "GDBuffer.h"
//#include "parser.h"
#include "mongo/client/dbclient.h"
using namespace std;
using namespace WriteDoc;
using namespace mongo;
class MGAgent{
	enum MGErrorCode{
		MG_OK=0x0,
		MG_CONN_FAIL=0x301,
		MG_IO=0x302,
		MG_DEFAULT
	};
	public:
		DBClientConnection *c;
		string serverHostnamelist;
		vector<string> serverHostname;
		string db;
		string collection;
		string ns;
		Error_Info conn();
		bool cancel;
	public:
		MGAgent(string const& serverHostnamelist,string const &db,string const &collection,string const& backupDir);
		Error_Info Init();
		Error_Info Put(GatherDoc const& gd);
		
		Error_Info Destroy();
		bool Cancel(){
			return cancel;
		}
};
#endif //CTAGENT_H
