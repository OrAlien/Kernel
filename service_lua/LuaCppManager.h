#ifndef __LUA_CPP_MANAGER_H__
#define __LUA_CPP_MANAGER_H__

#include <boost/unordered_map.hpp>

#include "LuaEventOut.h"
#include "LuaClientEventOut.h"
#include "MSSqlPool.h"
#include "MysqlPool.h"
#include "RedisPool.h"
#include "ObjectPool.h"
#include "DistributedService.h"
#include "LuaCppDefine.h"
#include "MutexLock.h"

class CLuaCppModule;

typedef Kernel::CActiveObjectMap<string, CLuaCppModule, Kernel::CMutexLock>			LuaCppModuleMap;
typedef Kernel::CActiveObjectMap<string, CDistributedService, Kernel::CMutexLock>	DistributeServiceMap;

/// @brief ģ�����
class CLuaCppManager
{
public:
	CLuaCppManager();
	~CLuaCppManager();

	static CLuaCppManager& Instance();

	/// @function ��ʼ��
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Init();

	/// @function ����
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Start();

	/// @function ֹͣ
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Stop();

	/// @function ���¼��ؽű�
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Reload();

	/// @function �������߼�������
	/// 
	/// @param name ������
	void SetMainLogic(string name) { m_MainLogicName = name; }

	/// @function ����ģ��
	/// 
	/// @param serviceName ������
	/// @param serviceName ������
	/// @param sciprtRootPath �ű���Ŀ¼
	/// @param serverRootPath ��ǰ���з������ű���Ŀ¼
	/// @param isCreate �Ƿ񴴽��������
	/// @return ���ؽ��
	CLuaCppModule* CreateModule(string serviceName, string scriptRootPath, string serverRootPath, bool isCreate = false);

	/// @function ����ģ��
	/// 
	/// @return ����ģ��
	CLuaCppModule* FindModule(string serviceName);

	/// @function �Ƴ�ģ��
	/// 
	/// @param serviceName ������
	void DestoryModule(string serviceName);

	/// @function ���
	/// 
	void Clear();

	/// @function �����¼����ӿ�
	/// 
	/// @param out �ӿڶ���
	void SetEventOut(IEventOut* out) { m_EventOut = out; m_LuaEventOut->SetEventOut(out); }

	/// @function ��ȡ�¼����ӿ�
	/// 
	/// @return �ӿڶ���
	IEventOut* GetEventOut() { return m_EventOut; }

	/// @function �����¼����ӿ�
	/// 
	/// @param out �ӿڶ���
	void SetClientEventOut(IClientOut* out) { m_ClientOut = out;  m_LuaClientEventOut->SetEventOut(out); }

	/// @function ��ȡ�¼����ӿ�
	/// 
	/// @return �ӿڶ���
	IClientOut* GetClientOut() { return m_ClientOut; }

	/// @function ��ȡ�¼����ӿ�
	/// 
	/// @return �ӿڶ���
	CLuaEventOut* GetLuaEventOut() { return m_LuaEventOut; }

	/// @function ��ȡ�¼����ӿ�
	/// 
	/// @return �ӿڶ���
	CLuaClientEventOut* GetLuaClientEventOut() { return m_LuaClientEventOut; }

	/// @function ��������
	/// 
	/// @param serviceName ������
	/// @param remoteAddr Զ�̷����ַ(�Ǳ��ط���)
	/// @param sessionID Զ�̷���Ựid(���ط���Ĭ��0)
	bool CreateService(string serviceName, const Kernel::CAddress* remoteAddr = NULL, double sessionID = 0);

	/// @function ���ҷ���
	/// 
	/// @param serviceName ������
	/// @return ���ط���
	CDistributedService* FindService(string serviceName);
	bool IsService(string serviceName);

	/// @function ɾ������
	/// 
	/// @param serviceName ������
	void DeleteService(string serviceName);

	/// @functioin �����������
	/// 
	/// @param srcService ���������
	/// @param detService Ŀ�������
	/// @param func �����ں���
	/// @param session �Ự
	/// @param param ����
	/// @return ���ط��ͽ��
	bool Send(string srcService, string detService, string func, string param);

	/// @functioin �����������
	/// 
	/// @param srcService ���������
	/// @param detService Ŀ�������
	/// @param func �����ں���
	/// @param param ����
	/// @param timeout ��ʱʱ��(0:������ʱ)
	/// @return ��������
	string Call(string srcService, string detService, string func, string param, int timeout);

private:
	CLuaEventOut*			m_LuaEventOut;				/// lua�������¼���
	CLuaClientEventOut*		m_LuaClientEventOut;		/// lua�ͻ����¼���
	IEventOut*				m_EventOut;					/// �������¼����ӿ�
	IClientOut*				m_ClientOut;				/// �ͻ����¼����ӿ�
	eServiceStatus			m_Status;					/// ״̬
	string					m_MainLogicName;			/// ���߼�������

	LuaCppModuleMap			m_LuaCppModuleMap;			/// ģ���б�
	DistributeServiceMap	m_DistributedServiceMap;	/// �����б�
};

// lua�¼��ӿ�
extern CLuaEventOut& GetServerLuaOut();
extern CLuaClientEventOut& GetClientLuaOut();

#ifdef _OPEN_DB_MODULE_

#ifdef __MSSQL_DB_MODULE__
extern Kernel::CMSSqlPool& GetMSSqlPool();
#endif //__MSSQL_DB_MODULE__

#ifdef __MYSQL_DB_MODULE__
extern Kernel::CMysqlPool& GetMysqlPool();
#endif //__MYSQL_DB_MODULE__

#ifdef __REDIS_DB_MODULE__
extern Kernel::CRedisPool& GetRedisPool();
#endif //__REDIS_DB_MODULE__

#endif //_OPEN_DB_MODULE_


#endif //__LUA_CPP_MANAGER_H__