
#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TSSLSocket.h>
#include <transport/TZlibTransport.h>
#include <transport/TTransportUtils.h>
#include <CacheTubeService.h>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include <fstream>
#include <assert.h>
#include "CacheTube.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::concurrency;

using namespace ::cachetube::thrift;

using namespace boost;
using namespace boost::xpressive;

namespace CacheTube {
	CCacheTube::Connection::Connection( void ) {
		m_strIP = "";
		m_iPort = -1; 
		m_Status = VALID;
	}
	CCacheTube::Connection::~Connection( void ) {
		m_strIP = "";
		m_iPort = -1; 
		m_Status = VALID;
	}
	CCacheTube::Connection & CCacheTube::Connection::operator=( CCacheTube::Connection const & con ) {
		m_strIP = con.m_strIP;
		m_iPort = con.m_iPort;
		m_Status = con.m_Status;
		return *this;
	}
	void CCacheTube::Connection::SetIP( ::std::string const & ip ) {
		assert( true != ip.empty() );
		m_strIP = ip;
	}
	::std::string CCacheTube::Connection::GetIP( void ) const {
		return m_strIP;
	}
	void CCacheTube::Connection::SetPort( int32_t const port ) {
		assert( 0 < port );
		m_iPort = port;
	}
	int32_t  CCacheTube::Connection::GetPort( void ) const {
		return m_iPort;
	}
	void CCacheTube::Connection::SetStatus( CCacheTube::Connection::ConnectionStatus const status ) {
		m_Status = status;
	}
	CCacheTube::Connection::ConnectionStatus CCacheTube::Connection::GetStatus( void ) const {
		return m_Status;
	}
	CCacheTube::CCacheTube( void ) {
		m_pSocket = NULL;
		m_pTransport = NULL;
		m_pProtocol = NULL;
		m_pClient = NULL;
	}
	CCacheTube::~CCacheTube( void ) {
		ReleaseContext();
		m_vConnections.clear();
	}
	int32_t CCacheTube::GetThriftExceptionType( const void * pCtx )const {		  		     	    			     
		TException * pTException = reinterpret_cast< TException * >( const_cast< void * >( pCtx ) );
		assert( NULL != pTException );
		if ( typeid( *pTException ) == typeid( TException ) ) {
			assert( 0 );
			return -1;
		} else if ( typeid( *pTException ) == typeid( TEOFException ) ) {
			return kErrCode_ErrTEOF;
		} else if ( typeid( *pTException ) == typeid( TSSLException ) ) {
			return kErrCode_ErrTSSL;
		} else if ( typeid( *pTException ) == typeid( TZlibTransportException ) ) {
			return kErrCode_ErrTZlib;
		} else if ( typeid( *pTException ) == typeid( TTransportException ) ) {
			return kErrCode_ErrTTransport;
		} else if ( typeid( *pTException ) == typeid( TProtocolException ) ) {
			return kErrCode_ErrTProtocol;
		} else if ( typeid( *pTException ) == typeid( TApplicationException ) ) {
			return kErrCode_ErrTApplication;
		} else if ( typeid( *pTException ) == typeid( SystemResourceException ) ) {
			return kErrCode_ErrTSystemResource;
		} else if ( typeid( *pTException ) == typeid( TooManyPendingTasksException ) ) {
			return kErrCode_ErrTIllegalState;   
		} else if ( typeid( *pTException ) == typeid( TimedOutException ) ) {
			return kErrCode_ErrTTimedOut;
		} else if ( typeid( *pTException ) == typeid( IllegalStateException ) ) {
			return kErrCode_ErrTIllegalState;
		} else if ( typeid( *pTException ) == typeid( Failure ) ) {
			return kErrCode_ErrTimeTunnel;
		} else {
			assert( 0 );
			return -1;
		}
	}
	Error_Info CCacheTube::LoadConfigfilePath( ::std::string const & configfile_path ) {
		assert( true != configfile_path.empty() );
		Error_Info e_info;
		::std::string strLine;
		::std::vector< ::std::string > vIPs;
		::std::vector< int32_t > vPorts;
		::std::vector< ::std::string >::iterator iter_vIPs;
		::std::vector< int32_t >::iterator iter_vPorts;
		cregex regComment = cregex::compile( "^[\\s]*#[\\d\\w\\s]*", icase );
		cregex regEmpty = cregex::compile( "^\\s*" );
		cregex regServerList = cregex::compile( "^\\s*server\\s+list\\s*=\\s*[\\d\\.,:]*", icase );
		cregex regIP = cregex::compile( "[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}" );
		cregex regPort = cregex::compile( ":[0-9]{1,5},?" );
		try {
			::std::ifstream in( configfile_path.c_str() );
			int32_t iCounter = 0;
			while ( true != in.eof() ) {
				(void)getline( in, strLine, '\n' );
				if ( true == regex_match( strLine.c_str(), regEmpty ) ) {
					continue;				
				} else if ( true == regex_match( strLine.c_str(), regComment ) ) {
					continue;
				} else if ( true == regex_match( strLine.c_str(), regServerList ) ) {			
					cregex_token_iterator posIP( strLine.c_str(), strLine.c_str() + strlen( strLine.c_str() ), regIP );
					cregex_token_iterator posPort( strLine.c_str(), strLine.c_str() + strlen( strLine.c_str() ) , regPort );
					vIPs.clear();
					vPorts.clear();
					while ( posIP != cregex_token_iterator() ) {
						vIPs.push_back( (*posIP).str() );
						++posIP;
					}
					::std::string strPort;
					while ( posPort != cregex_token_iterator() ) {
						strPort = (*posPort).str().substr( 1 );
						if ( ',' == strPort[ strPort.size()-1 ] ) {
							strPort = strPort.substr( 0, strPort.size()-1 );
						}
						vPorts.push_back( static_cast< int32_t >( atoi( strPort.c_str() ) ) );
						++posPort;
					}
					assert( true != vIPs.empty() );
					assert( true != vPorts.empty() );
					assert( vIPs.size() == vPorts.size() );
					if ( vIPs.size() != vPorts.size() ) {
						e_info.code = kErrCode_ErrUser;
						e_info.description = "IP number must be equal to Port number";
					}
					for ( iter_vIPs = vIPs.begin(), iter_vPorts = vPorts.begin(); ( ( iter_vIPs < vIPs.end() ) && ( iter_vPorts < vPorts.end() ) ); ++iter_vIPs, ++iter_vPorts ) {
						Connection conn;
						conn.SetIP( *iter_vIPs );
						conn.SetPort( *iter_vPorts );
						conn.SetStatus( Connection::VALID );
						m_vConnections.push_back( conn );
					}
					assert( vIPs.size() == m_vConnections.size() );
					assert( vPorts.size() == m_vConnections.size() );
				} else {
					assert( 0 );
				}
			}
			in.close();
		} catch ( ::std::exception const & e ) {
			e_info.code = kErrCode_ErrUser;
			e_info.description = ::std::string( e.what() );
			return e_info;
		}
		return e_info;
	}
	void ReleaseTransportContext( TTransport * const pThrans ) {
		return;
	}
	void ReleaseProtocolContext( TProtocol * const pProtocol ) {
		return;	
	}
	Error_Info CCacheTube::Init( ::std::string const & configfile_path ) {
		Error_Info e_info;
		assert( true != configfile_path.empty() );
		if ( true == configfile_path.empty() ) {
			e_info.code = kErrCode_ErrParameter;
			return e_info;
		}
		if ( NULL != m_pClient ) {
			e_info.code = kErrCode_ErrUser;
			e_info.description = "Initialized";
			return e_info;
		}
		e_info = LoadConfigfilePath( configfile_path ); 
		if ( kErrCode_OK != e_info.code ) {
			return e_info;
		}
		//::std::vector< ::std::string >::iterator iter_1;
		//::std::vector< int32_t >::iterator iter_2;
		//for ( iter_1 = m_vIPs.begin(); iter_1 != m_vIPs.end(); ++iter_1 ) {
		//	::std::cout<<*iter_1<<::std::endl;	
		//}
		//for ( iter_2 = m_vPorts.begin(); iter_2 != m_vPorts.end(); ++iter_2 ) {
		//	::std::cout<<*iter_2<<::std::endl;
		//}
		return 	Connect();
	}
	Error_Info CCacheTube::Put( ::std::string const & queue_name, ::std::vector< Message > const & v_msgs ) {
		Error_Info e_info;
		::std::vector< ::cachetube::thrift::Message > vThriftMsgs;
		::std::vector< Message >::const_iterator iter;
		if ( NULL == m_pClient ) {
			e_info.code = kErrCode_ErrUser;
			e_info.description = ::std::string( " uninitialized " );
			return e_info;
		}
		assert( true != queue_name.empty() );
		assert( true != v_msgs.empty() );
		assert( NULL != m_pSocket );
		assert( NULL != m_pTransport );
		assert( NULL != m_pProtocol );
		assert( NULL != m_pClient );
		if ( true == queue_name.empty() ) {
			e_info.code = kErrCode_ErrParameter;
			e_info.description = "topic can not be empty";
			return e_info;
		}
		if ( true == v_msgs.empty() ) {
			e_info.code = kErrCode_ErrParameter;
			e_info.description = "v_msgs can not be empty";
			return e_info;
		}
		for ( iter = v_msgs.begin(); iter < v_msgs.end(); ++iter ) {
			::cachetube::thrift::Message thriftMsg;
			thriftMsg.queue_name = iter->queue_name;
			thriftMsg.message_id = iter->uid;
			thriftMsg.source_ip = iter->srcip;
			thriftMsg.created_time = iter->created_time;
			thriftMsg.content = iter->content;
			vThriftMsgs.push_back( thriftMsg );
		}
		while ( true ) {
			try {
				if ( true != reinterpret_cast< TTransport * >( m_pTransport )->isOpen() ) {
					//e_info.code = kErrCode_ErrUser;
					//e_info.description = "Transport is closed";
					//return e_info;
					//::std::cout<<" Put Not Open "<<::std::endl;
					e_info = Connect();
					if ( kErrCode_OK != e_info.code ) {
						return e_info;
					}
					assert( kErrCode_OK == e_info.code );
				}
				reinterpret_cast< CacheTubeServiceClient * >( m_pClient )->post( queue_name, vThriftMsgs );
				break;
			} catch ( TException const & e ) {
				//e_info.code = GetThriftExceptionType( reinterpret_cast< const void * >( &e ) );
				//e_info.description = ::std::string( e.what() );
				//return e_info;
				//::std::cout<<" Put exception : code = "<<e_info.code<<" e_info.description = "<<e_info.description<<::std::endl;
				e_info = Connect();
				if ( kErrCode_OK != e_info.code ) {
					return e_info;
				}
			}
		}
		return e_info;
	}
	Error_Info CCacheTube::Get( ::std::string const & queue_name, ::std::vector< Message > & v_msgs ) {
		Error_Info e_info;
		::std::vector< ::cachetube::thrift::Message > vThriftMsgs;
		::std::vector< ::cachetube::thrift::Message >::iterator iter;
		if ( NULL == m_pClient ) {
			e_info.code = kErrCode_ErrUser;
			e_info.description = ::std::string( " uninitialized " );
			return e_info;
		}
		assert( true != queue_name.empty() );
		assert( NULL != m_pSocket );
		assert( NULL != m_pTransport );
		assert( NULL != m_pProtocol );
		assert( NULL != m_pClient );
		if ( true == queue_name.empty() ) {
			e_info.code = kErrCode_ErrParameter;
			e_info.description = "topic can not be empty";
			return e_info;
		}
		v_msgs.clear();
		while ( true ) {
			try {
				if ( true != reinterpret_cast< TTransport * >( m_pTransport )->isOpen() ) {
					//e_info.code = kErrCode_ErrUser;
					//e_info.description = "Transport is closed";
					e_info = Connect();
					if ( kErrCode_OK != e_info.code ) {
						return e_info;
					}
				}
				reinterpret_cast< CacheTubeServiceClient * >( m_pClient )->get( vThriftMsgs, queue_name );
				break;
			} catch ( TException const & e ) {
				//e_info.code = GetThriftExceptionType( reinterpret_cast< const void * >( &e ) );
				//e_info.description = ::std::string( e.what() );
				//return e_info;
				e_info = Connect();
				if ( kErrCode_OK != e_info.code ) {
					return e_info;
				}
			}
		}
		for ( iter = vThriftMsgs.begin(); iter < vThriftMsgs.end(); ++iter ) {
			Message msg;
			msg.queue_name = iter->queue_name;
			msg.srcip = iter->source_ip;
			msg.uid = iter->message_id;
			msg.created_time = iter->created_time;
			msg.content = iter->content;
			v_msgs.push_back( msg );
		}
		return e_info;
	}
	Error_Info CCacheTube::Destroy( void ) {
		Error_Info e_info;
		if ( NULL == m_pClient ) {
			e_info.code = kErrCode_ErrUser;
			e_info.description = ::std::string( " uninitialized " );
			return e_info;
		}
		assert( NULL != m_pSocket );
		assert( NULL != m_pTransport );
		assert( NULL != m_pProtocol );
		try {
			if ( true != reinterpret_cast< TTransport * >( m_pTransport )->isOpen() ) {
				return e_info;
			}
			reinterpret_cast< TTransport * >( m_pTransport )->close();	
		} catch ( TException const & e ) {
			ReleaseContext();	
			e_info.code = GetThriftExceptionType( reinterpret_cast< const void * >( &e ) );
			e_info.description = e.what();	
			return e_info;
		}
		ReleaseContext();
		return e_info;
	}
	void CCacheTube::ReleaseContext( void ) {
		if ( NULL !=  m_pSocket ) {
			delete reinterpret_cast< TSocket * >( m_pSocket );
		}
		if ( NULL != m_pTransport ) {
			delete reinterpret_cast< TTransport * >( m_pTransport );
		}
		if ( NULL != m_pProtocol ) {
			delete reinterpret_cast< TBinaryProtocol * >( m_pProtocol );
		}
		if ( NULL != m_pClient ) {
			delete reinterpret_cast< CacheTubeServiceClient * >( m_pClient );
		}
		m_pSocket = NULL;
		m_pTransport = NULL;
		m_pProtocol = NULL;
		m_pClient = NULL;
		return;
	}
	CCacheTube::Connection CCacheTube::FindNextValidConnection( void ) {
		Connection conn;
		::std::vector< Connection >::iterator iter;
		for ( iter = m_vConnections.begin(); iter < m_vConnections.end(); ++iter ) {
			if ( Connection::OCCUPIED == (*iter).GetStatus() ) {
				(*iter).SetStatus( Connection::INVALID );
			} else if ( Connection::VALID == (*iter).GetStatus() ) {
				conn = (*iter);
				(*iter).SetStatus( Connection::OCCUPIED );
				return conn;
			}
		}
		conn.SetStatus( Connection::INVALID );
		return conn;
 	}
	Error_Info CCacheTube::Connect( CCacheTube::Connection const & conn ) {
		assert( true != conn.GetIP().empty() );
		assert( 0 < conn.GetPort() );
		assert( Connection::VALID == conn.GetStatus() );
		Error_Info  e_info;
		ReleaseContext();
		try {
			m_pSocket = reinterpret_cast< void * >( new TSocket( conn.GetIP(), conn.GetPort() ) );
		} catch( ::std::bad_alloc const & eSocket ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( eSocket.what() );
			return e_info;	
		}
		assert( NULL != m_pSocket );
		if ( NULL == m_pSocket ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( "m_pSocket is NULL" );
			return e_info;
		}
		try {
			m_pTransport = reinterpret_cast< void * >( new TBufferedTransport( shared_ptr< TTransport >( reinterpret_cast< TTransport * >( m_pSocket ), ReleaseTransportContext ) ) );
		} catch ( ::std::bad_alloc const & eTransport ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( eTransport.what() );
			return e_info;
		}
		assert( NULL != m_pTransport );
		if ( NULL == m_pTransport ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( "m_pTransport is NULL" );
			return e_info;
		}
		try {
			m_pProtocol = reinterpret_cast< void * >( new TBinaryProtocol( shared_ptr< TTransport >( reinterpret_cast< TTransport * >( m_pTransport ), ReleaseTransportContext ) ) );
		} catch ( ::std::bad_alloc const & eProtocol ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( eProtocol.what() );
			return e_info;
		}
		assert( NULL != m_pProtocol );
		if ( NULL == m_pProtocol ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( "m_pProtocol is NULL" );
			return e_info;
		}
		try {
			m_pClient = reinterpret_cast< void * >( new CacheTubeServiceClient( shared_ptr< TProtocol >( reinterpret_cast< TProtocol * >( m_pProtocol ), ReleaseProtocolContext ) ) );
		} catch ( ::std::bad_alloc const & eClient ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( eClient.what() );
			return e_info;
		}
		assert( NULL != m_pClient );
		if ( NULL == m_pClient ) {
			ReleaseContext();
			e_info.code = kErrCode_ErrMemory;
			e_info.description = ::std::string( "m_pClient is NULL" );
			return e_info;
		}
		try {
			reinterpret_cast< TTransport* >( m_pTransport )->open();
		} catch ( TException const & e ) {
			ReleaseContext();
			e_info.code = GetThriftExceptionType( reinterpret_cast< const void * >( &e ) );
			e_info.description = ::std::string( e.what() );
			return e_info;
		}
		return e_info;
	}
	Error_Info CCacheTube::Connect( void ) {
		//::std::string strIP = "172.22.0.30";
		//int32_t   iPort = 12345;
		Error_Info e_info;
	    while ( true ) {
			Connection conn = FindNextValidConnection();
			if ( Connection::VALID == conn.GetStatus() ) {
				e_info = Connect( conn );
				if ( kErrCode_OK == e_info.code ) {
					return e_info;
				} else if ( kErrCode_ErrMemory == e_info.code ) {
					return e_info;
				} else if ( kErrCode_ErrTTransport == e_info.code ) {
					continue;
				}
			} else {
				assert( Connection::INVALID == conn.GetStatus() );
				e_info.code = kErrCode_ErrConnection;
				e_info.description = "can not find valid connection";
				return e_info;
			}
		}
		e_info.code = kErrCode_OK;
		return e_info;
	}
}

