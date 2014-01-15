/*!
*	\class CCacheTube
*	\brief 客户端接口
*	\date	 2012-2-23
*	\author	 michael(zhangtiey@software.ict.ac.cn)
*/
#ifndef CACHETUBE_H
#define CACHETUBE_H

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

namespace CacheTube {
	using namespace std;

	const int32_t kErrCode_OK = 0x00000000L;    // 正确
	const int32_t kErrCode_ErrMemory = 0x00000001L;  // 内存错误 new 出现错误
	const int32_t kErrCode_ErrParameter = 0x00000002L; // 参数错误 
	const int32_t kErrCode_ErrUser = 0x00000004L; // 内部逻辑错误

	/*thrift错误仅限CCacheTube内部使用*/
	const int32_t kErrCode_ErrTTransport = 0x00000008L;  // thrift 错误
	const int32_t kErrCode_ErrTProtocol = 0x00000010L;   // thrift 错误
	const int32_t kErrCode_ErrTApplication = 0x00000020L;  // thrift 错误
	const int32_t kErrCode_ErrTEOF = 0x00000040L;  // thrift 错误
	const int32_t kErrCode_ErrTSSL = 0x00000080L;  // thrift 错误
	const int32_t kErrCode_ErrTZlib = 0x00000100L; // thrift 错误
	const int32_t kErrCode_ErrTSystemResource = 0x00000200L; // thrift 错误
	const int32_t kErrCode_ErrTIllegalState = 0x00000400L; // thrift 错误
	const int32_t kErrCode_ErrTTimedOut = 0x00000800L; // thrift 错误
	const int32_t kErrCode_ErrTTooManyPendingTasks = 0x00001000L; // thrift 错误
	const int32_t kErrCode_ErrTimeTunnel = 0x00002000L; // thrift 错误

	const int32_t kErrCode_ErrConnection = 0x00004000L; // 无有效链接 配置文件中server_list指定的server都不可用
	

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
			int32_t				m_iPort;
			ConnectionStatus    m_Status;
		};
	public:
		//----------------------------------------------构造函数声明-------------------------------

		CCacheTube( void );
		/*函数说明
		*	\brief 构造函数
		*	\return	无
		*/

		virtual ~CCacheTube( void );
		/*函数说明
		*	\brief 析构函数	
		*	\return	无
		*/
	public:
		//----------------------------------------------公有成员接口-------------------------------
		Error_Info Init( ::std::string const & configfile_path );
		/*\brief	按照configfile_path指定的配置文件中的server_list地址对服务器进行链接
		* \param[in]	configfile_path 	   配置文件路径
		* \return	Error_Info
		*	\Error_Info.code = 错误码 可能是 kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection之一
		*	\Error_Info.description = 具体的错误描述
		*/

		Error_Info Put( ::std::string const & queue_name, ::std::vector< Message > const & v_msgs );
		/*函数说明
		*\brief 发送数据
		*\param [in] queue_name 队列名
		*\param [in] v_msgs  数据		
		*\return Error_Info
		*	\Error_Info.code = 错误码 可能是 kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection之一
		*	\Error_Info.description = 具体的错误描述 
		*/		

		Error_Info Get( ::std::string const & queue_name, ::std::vector< Message > & v_msgs ); 
		/*函数说明
		*\brief 读取数据
		*\param [in]  queue_name 队列名
		*\param [out] list_msgs 返回的数据	
		*\return Error_Info
		*	\Error_Info.code = 错误码 可能是 kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection之一
		*	\Error_Info.description = 具体的错误描述
		*/	

		Error_Info Destroy( void );
		/*函数说明
		*\brief  关闭链接 释放资源
		*\return Error_Info
		*	\Error_Info.code = 错误码 可能是 kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection之一
		*	\Error_Info.description = 具体的错误描述
		*/

	protected:
		//Error_Info Ack(  ::std::string const & queue_name, ::std::vector< Message > const & v_msgs  );  // 在Get的最后被调用，确认正确的得到了数据
        int32_t GetThriftExceptionType( const void * pCtx ) const;
		void	ReleaseContext( void );
		Error_Info LoadConfigfilePath( ::std::string const & configfile_path );
		Connection FindNextValidConnection( void );
		Error_Info Connect( Connection const & conn );
		Error_Info Connect( void );
		Error_Info ctloadServerlist(string server_list);
		void * m_pSocket;     // void* 是为了不用添加thrift的相关头文件
		void * m_pTransport;  // void* 是为了不用添加thrift的相关头文件
		void * m_pProtocol;   // void* 是为了不用添加thrift的相关头文件
		void * m_pClient;     // void* 是为了不用添加thrift的相关头文件
	public:
		::std::vector< Connection >  m_vConnections;   
		bool ctDebug;
		bool ctBlocked;
		vector<string> ctServerHostname;
		int ctagentIndex;
	};
}
#endif // 
