#ifndef HBAGENT_H
#define HBAGENT_H
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>
#include "Hbase.h"
#include "WriteDoc.h"
#include "json/json.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace apache::hadoop::hbase::thrift;
using namespace std;
using namespace WriteDoc;
//static int HBaseThriftVersion=1;
class HBAgent{
	enum HBaseThriftError{
		HB_OK=0x0,
		HB_IO_HBASE=0x200,//begin from 0x100
		HB_CONN_FAIL=0x202,
		HB_READZOOKEEPER_FAIL=0x203,
		HB_BADZOOKEEPER_CONFIG=0x204,
		HB_INVAID_ARGS=0x205
		
		
	};
	private:
		HbaseClient *c;
		vector<string> serverHostname;
		int currentServer;
		string collection;
		string columnfamily;
		Error_Info conn();
		Error_Info readZookeeper();
		string zookeeperAddress;
		string md5Column;
	public:
		HBAgent(string const& serverHostnamelist,string const &zookeeperAddress);
		Error_Info Init();
		Error_Info Put(GatherDoc const& gd);
		
		Error_Info Destroy();
};
#endif //CTAGENT_H
