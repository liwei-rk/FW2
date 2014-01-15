#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <vector>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include "./gen-cpp/CacheTubeService_types.h"
#include "./gen-cpp/CacheTubeService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace boost;

using namespace ::cachetube::thrift;

int main(int argc, char** argv) {
	shared_ptr<TTransport> socket(new TSocket("172.22.0.30", 12345));
	shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	CacheTubeServiceClient client(protocol);

	try {
		transport->open();
		::std::vector< ::cachetube::thrift::Message > v_msg;
		::std::vector< ::cachetube::thrift::Message >::iterator iter;
		::std::string strTopicName = "topic1";	
		char temp[ 10 ];
		::cachetube::thrift::Message msg;
		msg.queue_name  = strTopicName;
		msg.source_ip   = "www.google.com:8080/justfortest";
		msg.created_time = 0x7fffffffFEDCBALL;
		for (int i = 0; i < 100; ++i) {
			v_msg.push_back( msg );	
		}
		uint32_t  uCounter_post = 0;
		uint32_t  uCounter = 0;
		struct timeval  timeStart;
		struct timeval  timeEnd;
		(void)gettimeofday( &timeStart, NULL );
		while( true ) {
			for ( iter = v_msg.begin(); iter < v_msg.end(); ++iter ) {
				(*iter).message_id = uCounter;
				sprintf( temp, "%d", uCounter );	
				(*iter).content = ::std::string( temp );
				uCounter++;
			}
			client.post( strTopicName, v_msg );
			uCounter_post++;
			if ( 0 == uCounter_post%50 ) {
				(void)gettimeofday( &timeEnd, NULL );
				printf(" post: %u count %u s %u ms \n", uCounter_post, static_cast<uint64_t>(timeEnd.tv_sec) - static_cast<uint64_t>(timeStart.tv_sec), static_cast<uint64_t>( timeEnd.tv_usec ) - static_cast<uint64_t>( timeStart.tv_usec ) );
				(void)gettimeofday( &timeStart, NULL );
			}
		}
		transport->close();
	} catch (TException &tx) {
		printf("ERROR: %s\n", tx.what());
	}

}
