/*!
*	\class CCacheTube
*	\brief 客户端接口
*	\date	 2012-2-23
*/
#ifndef CACHETUBE_H
#define CACHETUBE_H
#include <stdint.h>
#include <string>
#include <vector>
namespace CacheTube {
	const int32_t kErrCode_OK = 0x00000000L;
	const int32_t kErrCode_ErrMemory = 0x00000001L;
	const int32_t kErrCode_ErrParameter = 0x00000002L;
	const int32_t kErrCode_ErrUser = 0x00000004L;
	const int32_t kErrCode_ErrTTransport = 0x00000008L;
	const int32_t kErrCode_ErrTProtocol = 0x00000010L;
	const int32_t kErrCode_ErrTApplication = 0x00000020L;
	const int32_t kErrCode_ErrTEOF = 0x00000040L;
	const int32_t kErrCode_ErrTSSL = 0x00000080L;
	const int32_t kErrCode_ErrTZlib = 0x00000100L;
	const int32_t kErrCode_ErrTSystemResource = 0x00000200L;
	const int32_t kErrCode_ErrTIllegalState = 0x00000400L;
	const int32_t kErrCode_ErrTTimedOut = 0x00000800L;
	const int32_t kErrCode_ErrTTooManyPendingTasks = 0x00001000L;
	const int32_t kErrCode_ErrTimeTunnel = 0x00002000L;
	const int32_t kErrCode_ErrConnection = 0x00004000L;
	struct Message { /* 消息结构 */
		::std::string queue_name;    /*  消息所属的队列名字 */ 
			int64_t uid;						/*  消息ID*/
			::std::string srcip;         /*  消息来源ip 默认自动填充本机IP*/
			int64_t created_time; /*  消息入库时间, 采集器不填 */
			::std::string content;      	/*  消息的内容, json格式, 默认为"" */		
			Message(){
				queue_name = "";
				uid = 0;
				srcip = "";
				created_time = 0;
				content = "";
		}		
	};

	struct Error_Info { /* 错误信息数据结构 */
		int32_t code;					/*  错误编号,0为正确返回 */
			::std::string  description;       		/*  错误信息描述 */
		Error_Info() {
			code = kErrCode_OK;
		}
	};

	class CCacheTube
	{
	public:
		class Connection 
		{
		friend class CCacheTube;
		public:
			enum ConnectionStatus {
				VALID = 0,
				INVALID,
				OCCUPIED
			};
		public:
			Connection( void );
			virtual ~Connection( void );
			Connection & operator=( Connection const & con );
		public:
			void SetIP( ::std::string const & ip );
			::std::string GetIP( void ) const;
			void SetPort( int32_t const port );
			int32_t  GetPort( void ) const;
			void SetStatus( ConnectionStatus const status );
			ConnectionStatus GetStatus( void ) const;
		protected:
			::std::string		m_strIP;
			int32_t			m_iPort;
			ConnectionStatus    	m_Status;
		};
	public:
		//----------------------------------------------构造函数声明-------------------------------

		CCacheTube( void );
		/*函数说明
		*	\brief 构造函数
		*	\param [in]  无
		*	\return	无
		*	\author michael
		*	\date  2012-2-15
		*/


		virtual ~CCacheTube( void );
		/*函数说明
		*	\brief 析构函数	
		*	\return	无
		*	\author michael
		*	\date  2012-2-15
		*/
	public:
		//----------------------------------------------公有成员接口-------------------------------

		Error_Info Init( ::std::string const & configfile_path );
		/*函数说明,内嵌string serverlist, string username, string password
		*	\brief 客户端连接设置,代理服务器（thrift java）运行在本地, 首先执行thrift连接到本地java代理
		*        服务端，代理服务端调用CacheTube的java客户端
		* \configfile_path 			 配置文件路径，提供缺省值
		*	\param [in] serverlist 为远程CacheTube的服务地址列表, 以逗号隔开形式为172.22.0.30:9090,***
		*	\param [in] username   在CacheTube服务器上的用户名
		*	\param [in] password	 在CacheTube服务器上的密码
		* \return 成功返回0, 否则为错误值
		*	\author michael
		*	\date 2012-2-23
		*/


		Error_Info Put( ::std::string const & queue_name, ::std::vector< Message > const & v_msgs );
		/*函数说明
		*	\brief 发送数据接口
		*	\param [in] list_msg		该批发送的数据内容
		*	\param [in] topic       队列名			
		*	\return	返回发送状态信息
		*	\author michael
		*	\date 2012-2-23
		*/

		Error_Info Get( ::std::string const & queue_name, ::std::vector< Message > & v_msgs ); //??是否需要单独订阅设置
		/*函数说明
		*	\brief 订阅数据并返回结果
		*	\param [in]  topic       	队列名
		*	\param [out] list_msgs		返回的内容	
		*	\return 返回状态信息
		*	\author michael
		*	\date 2012-2-23
		*/

		Error_Info Destroy( void );
		/*函数说明
		*	\brief 释放资源, 包括关闭java服务代理以及调用CacheTube服务端的release
		*	\return 无
		*	\author michael
		*	\date 2012-2-23
		*/

		/*
		void SetDatabaseURI(string URI, string username, string password);
		//函数说明:是否需要？多租户角度是需要的，有各自的需求，放在broker里的配置文件
		*	\brief 设置mongodb的URI  
		*	\param [in] URI					形式为172.22.0.30:9090
		*	\param [in] username 
		*	\param [in] password
		*	\return 无
		*	\author michael
		*	\date 2012-2-23
		*/

	//private:
	//	shared_ptr<TTransport> m_ptrSocket;
	//	shared_ptr<TTransport> m_ptrTransport;
	//	shared_ptr<TProtocol> m_prtProtocol;
	//	CacheTubeServiceClient* m_ptrServiceClient;
	protected:
        int32_t GetThriftExceptionType( const void * pCtx ) const;
		void	ReleaseContext( void );
		Error_Info LoadConfigfilePath( ::std::string const & configfile_path );
		Connection FindNextValidConnection( void );
		Error_Info Connect( Connection const & conn );
		Error_Info Connect( void );
	protected:
		void * m_pSocket;
		void * m_pTransport;
		void * m_pProtocol;
		void * m_pClient;
		::std::vector< Connection >  m_vConnections;
	};
}
#endif // 
