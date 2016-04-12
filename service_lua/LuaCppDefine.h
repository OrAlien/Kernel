#ifndef __LUA_CPP_DEFINE_H__
#define __LUA_CPP_DEFINE_H__

//////////////////////////////////////////////////////////////////////////
/// lua����������

// ���߼�
#define MAIN_LOGIC			"main_logic"

// ���ݿ��߼�
#define DB_LOGIC			"db_logic"


//////////////////////////////////////////////////////////////////////////
/// lua ������������ key

/// �ű���Ŀ¼
#define SCRIPT_ROOT_PATH	"script_root_path"	

/// ��ǰ���з������ű���Ŀ¼
#define SERVER_ROOT_PATH	"server_root_path"

// ������
#define SERVICE_NAME		"service_name"


//////////////////////////////////////////////////////////////////////////


// ����״̬
enum eServiceStatus
{
	SERVICE_STATUS_NULL,		// ��״̬
	SERVICE_STATUS_INIT,		// ��ʼ��
	SERVICE_STATUS_START,		// ��ʼ
	SERVICE_STATUS_STOP			// ֹͣ
};



#endif //__LUA_CPP_DEFINE_H__