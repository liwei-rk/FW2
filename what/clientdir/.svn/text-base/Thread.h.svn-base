#ifndef  _CACHETUBE_H__
#define  _CACHETUBE_H__
#include <pthread.h>
#include <iostream>
namespace  CacheTube {
	class Thread
	{
	public:
		Thread( void );
		virtual ~Thread( void );
	public:
		bool Start( void );
		bool Join( void );
	public:
		static void * CallBack( void * arg );
	protected:
		virtual int32_t Entry( void ) = 0;
	public:
		::std::string m_strThreadID;
		::std::string m_strConfPath;
		::std::string m_strTopic;
		pthread_t     m_Thread;
	};
}
#endif /// #define  _CACHETUBE_H__
