/*!
*	\class CCacheTube
*	\brief �ͻ��˽ӿ�
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
	struct Message { /* ��Ϣ�ṹ */
		::std::string queue_name;    /*  ��Ϣ�����Ķ������� */ 
			int64_t uid;						/*  ��ϢID*/
			::std::string srcip;         /*  ��Ϣ��Դip Ĭ���Զ���䱾��IP*/
			int64_t created_time; /*  ��Ϣ���ʱ��, �ɼ������� */
			::std::string content;      	/*  ��Ϣ������, json��ʽ, Ĭ��Ϊ"" */		
			Message(){
				queue_name = "";
				uid = 0;
				srcip = "";
				created_time = 0;
				content = "";
		}		
	};

	struct Error_Info { /* ������Ϣ���ݽṹ */
		int32_t code;					/*  ������,0Ϊ��ȷ���� */
			::std::string  description;       		/*  ������Ϣ���� */
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
		//----------------------------------------------���캯������-------------------------------

		CCacheTube( void );
		/*����˵��
		*	\brief ���캯��
		*	\param [in]  ��
		*	\return	��
		*	\author michael
		*	\date  2012-2-15
		*/


		virtual ~CCacheTube( void );
		/*����˵��
		*	\brief ��������	
		*	\return	��
		*	\author michael
		*	\date  2012-2-15
		*/
	public:
		//----------------------------------------------���г�Ա�ӿ�-------------------------------

		Error_Info Init( ::std::string const & configfile_path );
		/*����˵��,��Ƕstring serverlist, string username, string password
		*	\brief �ͻ�����������,�����������thrift java�������ڱ���, ����ִ��thrift���ӵ�����java����
		*        ����ˣ��������˵���CacheTube��java�ͻ���
		* \configfile_path 			 �����ļ�·�����ṩȱʡֵ
		*	\param [in] serverlist ΪԶ��CacheTube�ķ����ַ�б�, �Զ��Ÿ�����ʽΪ172.22.0.30:9090,***
		*	\param [in] username   ��CacheTube�������ϵ��û���
		*	\param [in] password	 ��CacheTube�������ϵ�����
		* \return �ɹ�����0, ����Ϊ����ֵ
		*	\author michael
		*	\date 2012-2-23
		*/


		Error_Info Put( ::std::string const & queue_name, ::std::vector< Message > const & v_msgs );
		/*����˵��
		*	\brief �������ݽӿ�
		*	\param [in] list_msg		�������͵���������
		*	\param [in] topic       ������			
		*	\return	���ط���״̬��Ϣ
		*	\author michael
		*	\date 2012-2-23
		*/

		Error_Info Get( ::std::string const & queue_name, ::std::vector< Message > & v_msgs ); //??�Ƿ���Ҫ������������
		/*����˵��
		*	\brief �������ݲ����ؽ��
		*	\param [in]  topic       	������
		*	\param [out] list_msgs		���ص�����	
		*	\return ����״̬��Ϣ
		*	\author michael
		*	\date 2012-2-23
		*/

		Error_Info Destroy( void );
		/*����˵��
		*	\brief �ͷ���Դ, �����ر�java��������Լ�����CacheTube����˵�release
		*	\return ��
		*	\author michael
		*	\date 2012-2-23
		*/

		/*
		void SetDatabaseURI(string URI, string username, string password);
		//����˵��:�Ƿ���Ҫ�����⻧�Ƕ�����Ҫ�ģ��и��Ե����󣬷���broker��������ļ�
		*	\brief ����mongodb��URI  
		*	\param [in] URI					��ʽΪ172.22.0.30:9090
		*	\param [in] username 
		*	\param [in] password
		*	\return ��
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
