/*!
*	\class CCacheTube
*	\brief �ͻ��˽ӿ�
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

	const int32_t kErrCode_OK = 0x00000000L;    // ��ȷ
	const int32_t kErrCode_ErrMemory = 0x00000001L;  // �ڴ���� new ���ִ���
	const int32_t kErrCode_ErrParameter = 0x00000002L; // �������� 
	const int32_t kErrCode_ErrUser = 0x00000004L; // �ڲ��߼�����

	/*thrift�������CCacheTube�ڲ�ʹ��*/
	const int32_t kErrCode_ErrTTransport = 0x00000008L;  // thrift ����
	const int32_t kErrCode_ErrTProtocol = 0x00000010L;   // thrift ����
	const int32_t kErrCode_ErrTApplication = 0x00000020L;  // thrift ����
	const int32_t kErrCode_ErrTEOF = 0x00000040L;  // thrift ����
	const int32_t kErrCode_ErrTSSL = 0x00000080L;  // thrift ����
	const int32_t kErrCode_ErrTZlib = 0x00000100L; // thrift ����
	const int32_t kErrCode_ErrTSystemResource = 0x00000200L; // thrift ����
	const int32_t kErrCode_ErrTIllegalState = 0x00000400L; // thrift ����
	const int32_t kErrCode_ErrTTimedOut = 0x00000800L; // thrift ����
	const int32_t kErrCode_ErrTTooManyPendingTasks = 0x00001000L; // thrift ����
	const int32_t kErrCode_ErrTimeTunnel = 0x00002000L; // thrift ����

	const int32_t kErrCode_ErrConnection = 0x00004000L; // ����Ч���� �����ļ���server_listָ����server��������
	

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
			int32_t				m_iPort;
			ConnectionStatus    m_Status;
		};
	public:
		//----------------------------------------------���캯������-------------------------------

		CCacheTube( void );
		/*����˵��
		*	\brief ���캯��
		*	\return	��
		*/

		virtual ~CCacheTube( void );
		/*����˵��
		*	\brief ��������	
		*	\return	��
		*/
	public:
		//----------------------------------------------���г�Ա�ӿ�-------------------------------
		Error_Info Init( ::std::string const & configfile_path );
		/*\brief	����configfile_pathָ���������ļ��е�server_list��ַ�Է�������������
		* \param[in]	configfile_path 	   �����ļ�·��
		* \return	Error_Info
		*	\Error_Info.code = ������ ������ kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection֮һ
		*	\Error_Info.description = ����Ĵ�������
		*/

		Error_Info Put( ::std::string const & queue_name, ::std::vector< Message > const & v_msgs );
		/*����˵��
		*\brief ��������
		*\param [in] queue_name ������
		*\param [in] v_msgs  ����		
		*\return Error_Info
		*	\Error_Info.code = ������ ������ kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection֮һ
		*	\Error_Info.description = ����Ĵ������� 
		*/		

		Error_Info Get( ::std::string const & queue_name, ::std::vector< Message > & v_msgs ); 
		/*����˵��
		*\brief ��ȡ����
		*\param [in]  queue_name ������
		*\param [out] list_msgs ���ص�����	
		*\return Error_Info
		*	\Error_Info.code = ������ ������ kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection֮һ
		*	\Error_Info.description = ����Ĵ�������
		*/	

		Error_Info Destroy( void );
		/*����˵��
		*\brief  �ر����� �ͷ���Դ
		*\return Error_Info
		*	\Error_Info.code = ������ ������ kErrCode_OK kErrCode_ErrMemory kErrCode_ErrParameter kErrCode_ErrUserk ErrCode_ErrConnection֮һ
		*	\Error_Info.description = ����Ĵ�������
		*/

	protected:
		//Error_Info Ack(  ::std::string const & queue_name, ::std::vector< Message > const & v_msgs  );  // ��Get����󱻵��ã�ȷ����ȷ�ĵõ�������
        int32_t GetThriftExceptionType( const void * pCtx ) const;
		void	ReleaseContext( void );
		Error_Info LoadConfigfilePath( ::std::string const & configfile_path );
		Connection FindNextValidConnection( void );
		Error_Info Connect( Connection const & conn );
		Error_Info Connect( void );
		Error_Info ctloadServerlist(string server_list);
		void * m_pSocket;     // void* ��Ϊ�˲������thrift�����ͷ�ļ�
		void * m_pTransport;  // void* ��Ϊ�˲������thrift�����ͷ�ļ�
		void * m_pProtocol;   // void* ��Ϊ�˲������thrift�����ͷ�ļ�
		void * m_pClient;     // void* ��Ϊ�˲������thrift�����ͷ�ļ�
	public:
		::std::vector< Connection >  m_vConnections;   
		bool ctDebug;
		bool ctBlocked;
		vector<string> ctServerHostname;
		int ctagentIndex;
	};
}
#endif // 
