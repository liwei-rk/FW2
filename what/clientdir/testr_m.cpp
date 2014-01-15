
#include "CacheTube.h"
#include "Thread.h"
#include <iostream>
#include <fstream>
#include <assert.h>
namespace CacheTube {
	class ReadingThread : public Thread
	{
	public:
		static const int32_t kNumberOfReadingThread = 5;
	public:
		ReadingThread( void ) {	
		}
		virtual ~ReadingThread( void ) {	
		}
	public:
		virtual int32_t Entry( void ) {
			Error_Info e_info;
			CCacheTube cacheTube;
			::std::string strConfPath = m_strConfPath;
			::std::string strTopic = m_strTopic;
			::std::vector< Message > v_msgs;
			::std::vector< Message >::iterator iter;
			e_info = cacheTube.Init( strConfPath );
			if ( kErrCode_OK != e_info.code ) {
				::std::cout<<m_strThreadID<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
				return -1;
			}
			::std::cout<<m_strThreadID<<" Init OK! "<<::std::endl;
			::std::string strOutPutPath = ::std::string( "./" ) + m_strThreadID + ::std::string( "_r.out" );
			::std::ofstream out( strOutPutPath.c_str() ); 
			uint32_t  uCounter_Get = 0;	
			while ( true ) {
				v_msgs.clear();
				e_info = cacheTube.Get( strTopic, v_msgs );
				if ( kErrCode_OK != e_info.code ) {
					::std::cout<<m_strThreadID<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
					out.close();
					return -1;
				}
				try {
					for ( iter = v_msgs.begin(); iter != v_msgs.end(); ++iter ) {
						out<<iter->queue_name<<" "<<iter->uid<<" "<<iter->srcip<<" "<<iter->created_time<<" "<<iter->content<<::std::endl;
					}
				} catch ( ... ) {
					::std::cout<<m_strThreadID<<" write file exception"<<::std::endl;
					out.close();
					return -1;	
				}
				uCounter_Get++;
				if ( uCounter_Get%50 == 0 ) {
					::std::cout<<m_strThreadID<<" Get: "<< uCounter_Get <<::std::endl;
				}	
			}
			out.close();
			e_info = cacheTube.Destroy();
			if ( kErrCode_OK != e_info.code ) {
				::std::cout<<m_strThreadID<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
				return -1;
			}
			::std::cout<<m_strThreadID<<" Destroy OK! "<<::std::endl;
			return 0;
		}
	};
	extern "C"	int main( int argc, char * argv[] )
	{
		assert( 3 == argc );
		::std::string strConfPath = ::std::string( argv[ 1 ] );
		::std::string strTopic = ::std::string( argv[ 2 ] );
		int32_t i = 0;
		char temp[ 10 ];
		ReadingThread  threadArray[ ReadingThread::kNumberOfReadingThread ];
		for ( i = 0; i < ReadingThread::kNumberOfReadingThread; ++i ) {
			(void)sprintf( temp, "ReadingThread_%d", i );
			threadArray[ i ].m_strThreadID = ::std::string( temp );
			threadArray[ i ].m_strConfPath = strConfPath;
			threadArray[ i ].m_strTopic = strTopic;
			if ( false == threadArray[ i ].Start() ) {
				return -1;
			}
		}
		for ( i = 0; i < ReadingThread::kNumberOfReadingThread; ++i ) {
			if ( false == threadArray[ i ].Join() ) {
				return -1;
			}
		}
		return 0;
	}
}

