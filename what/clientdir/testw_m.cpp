
#include "CacheTube.h"
#include "Thread.h"
#include <iostream>
#include <sys/time.h>
#include <pthread.h>
#include <fstream>
#include <assert.h>
namespace CacheTube {
	class WritingThread : public Thread
	{
		typedef  Thread  inherited_t;
	public:
		static const int32_t kNumberOfWritingThread = 10;
	public:
		WritingThread( void ) : inherited_t() {
		}
		virtual ~WritingThread( void ) {
		}
	protected:
		virtual int32_t Entry( void ) {
			Error_Info e_info;
			CCacheTube cacheTube;
			::std::string strConfPath = m_strConfPath;
			::std::string strTopic = m_strTopic;
			::std::vector< Message > v_msgs;
			::std::vector< Message >::iterator iter;
			e_info = cacheTube.Init( strConfPath );
			if ( kErrCode_OK != e_info.code ) {
				::std::cout<<m_strThreadID<<" Error Code = "<<e_info.code<<" Description = "<<e_info.description<<::std::endl;
				return -1;
			}
			::std::cout<<m_strThreadID<<" Init OK! "<<::std::endl;
			v_msgs.clear();
			Message msg;
			int32_t i = 0;
			::std::string strContent;
			for ( i = 0; i < 2028; ++i ) {
				strContent += static_cast<char>( 'A' + i%24 );	
			}
			for ( i = 0; i < 20; ++i ) {
				msg.queue_name = strTopic;
				//msg.srcip = "123.123.123.123";
				(void)time( &msg.created_time );
				msg.content = strContent;
				v_msgs.push_back( msg );
			}
			//::std::string strOutputPath = ::std::string( "./" ) + m_strThreadID + ::std::string( "_w.out" ) ;
			//::std::ofstream out( strOutputPath.c_str() );
			uint32_t uCounter = 0;
			uint32_t uCounter_Put = 0;
			char temp[ 10 ];
			struct timeval timeStart;
			struct timeval timeEnd;
			(void)gettimeofday( &timeStart, NULL ); 
			while ( true ) {
				uCounter_Put++;
				for ( iter = v_msgs.begin(); iter < v_msgs.end(); ++iter ) {
					(*iter).uid = uCounter;
					sprintf( temp, "%d", uCounter );
					(*iter).srcip = temp;
					uCounter++;
				}
				e_info = cacheTube.Put( strTopic, v_msgs );
				//for ( iter = v_msgs.begin(); iter < v_msgs.end(); ++iter ) {
					//out<<(*iter).queue_name<<" "<<(*iter).uid<<" "<<(*iter).srcip<<" "<<(*iter).created_time<<" "<<(*iter).content<<::std::endl;	
				//}
				if ( kErrCode_OK != e_info.code ) {
					::std::cout<<m_strThreadID<<" Error Code = "<<e_info.code<<" Description = "<<e_info.description<<::std::endl;
					//out.close();
					return -1;
				}
				if ( 0 == uCounter_Put%50 ) {
					(void)gettimeofday( &timeEnd, NULL ); 
					printf("%s Put: %u Counter %lu s %lu ms \n", m_strThreadID.c_str(), uCounter_Put, static_cast<uint64_t>( timeEnd.tv_sec ) - static_cast<uint64_t>( timeStart.tv_sec ),
						static_cast<uint64_t>( timeEnd.tv_usec ) - static_cast<uint64_t>( timeStart.tv_usec ) );
					(void)gettimeofday( &timeStart, NULL );
				}
				if ( 1000 == uCounter_Put ) {
					break;
				}	
				sleep(1);
			}
			//out.close();
			::std::cout<<m_strThreadID<<" Put OK! "<<::std::endl;
			e_info = cacheTube.Destroy();
			if ( kErrCode_OK != e_info.code ) {
				::std::cout<<m_strThreadID<<" Error Code = "<<e_info.code<<" Description = "<<e_info.description<<::std::endl;
				return -1;
			}
			::std::cout<<m_strThreadID<<" Destroy OK! "<<::std::endl;
			return 0;
		}
	};
	extern "C" int main( int argc, char * argv[] )
	{
		assert( 3 == argc );
		::std::string strConfPath = ::std::string( argv[ 1 ] );
		::std::string strTopic = ::std::string( argv[ 2 ] );
		int32_t i = 0;
		char temp[ 10 ];
		WritingThread  threadArray[ WritingThread::kNumberOfWritingThread ];
		for ( i = 0; i < WritingThread::kNumberOfWritingThread; ++i ) {
			(void)sprintf( temp, "WritingThread_%d", i );
			threadArray[ i ].m_strThreadID = ::std::string( temp );
			threadArray[ i ].m_strConfPath = strConfPath;
			threadArray[ i ].m_strTopic = strTopic;
			if ( false == threadArray[ i ].Start() ) {
				return -1;
			}
		}
		for ( i = 0; i < WritingThread::kNumberOfWritingThread; ++i ) {
			if ( false == threadArray[ i ].Join() ) {
				return -1;
			}
		}
	}
}

