#ifndef __DISTRIBUTED_SERVICE_H__
#define __DISTRIBUTED_SERVICE_H__

#include "Types.h"
#include "BlockQueue.h"
#include "Address.h"
#include "LuaCppModule.h"
#include "LuaCppDefine.h"
#include "ThreadPackage.h"
#include "MutexLock.h"

typedef Kernel::CLockfreeBlockQueue<Kernel::CTEventPackage*>	DistributedQueue;		/// �������
typedef Kernel::CLockfreeBlockQueue<Kernel::CTEventPackage*, Kernel::CMutexLock, false, 3000> CallServiceQueue;	/// ������ö���

// �ֲ�ʽ����
class CDistributedService
{
public:
	CDistributedService(string serviceName, const Kernel::CAddress* remoteAddr = NULL, bool isCreate = false);
	~CDistributedService();

	/// @functin ��ʼ��
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Init();

	/// @function ����������
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Start();

	/// @function ֹͣ������
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Stop();

	/// @function �Ƿ��Ǳ��ط���
	/// 
	bool IsLocalService() { return m_LoaclService; }

	/// @function ����luaģ��
	/// 
	void SetLuaMoudle(CLuaCppModule* moudle) { m_LuaModule = moudle; }

	/// @function ��ȡ�������
	/// 
	/// @return ���ض���
	DistributedQueue* GetQueue() { return m_ServiceQueue; }

	/// @functioin �����������
	/// 
	/// @param serviceName ������
	/// @param func �����ں���
	/// @param session �Ự
	/// @param param ����
	/// @return ���ط��ͽ��
	bool Send(string serviceName, string func, string param);

	/// @functioin �����������
	/// 
	/// @param serviceName ������
	/// @param func �����ں���
	/// @param param ����
	/// @param timeout ��ʱʱ��(0:������ʱ)
	/// @return ��������
	string Call(string serviceName, string func, string param, int timeout = 3000);

	/// @function ����
	/// 
	void Run();

protected:
	bool					m_IsRunning;			/// �Ƿ�����
	bool					m_LoaclService;			/// �Ƿ񱾵ط���
	bool					m_IsCreateQueue;		/// �Ƿ񴴽��������
	string					m_ServiceName;			/// ��������
	DistributedQueue*		m_ServiceQueue;			/// �������
	Kernel::CAddress		m_RemoteAddr;			/// Զ�̷����ַ
	uint64_t				m_SessionID;			/// Զ�̷���Ự

	CLuaCppModule*			m_LuaModule;			/// luaģ��
	eServiceStatus			m_Status;				/// ״̬
	CallServiceQueue		m_CallWait;				/// ����call���õȴ�

}; // end class CDistributedService

#endif //__DISTRIBUTE_SERVICE_H__