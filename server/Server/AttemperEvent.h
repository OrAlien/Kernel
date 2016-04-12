#ifndef __ATTEMPER_EVENT_H__
#define __ATTEMPER_EVENT_H__

#include "IEventIn.h"
#include "IEventOut.h"
#include "IClientOut.h"

#ifdef _OPEN_LUA_MODULE_
#include "LuaCppModule.h"
#include "LuaCppManager.h"
#include "LuaCppDefine.h"
#include <boost/interprocess/ipc/message_queue.hpp>
#endif

using namespace boost::interprocess;

/// @Brief �¼����ӿ�, ���ر������¼���Դ��Ĭ����logic thread
class CAttemperEvent : public IEventIn
{
public:
	CAttemperEvent();
	~CAttemperEvent();

	static CAttemperEvent& Instance();

	//////////////////////////////////////////////////////////////////////////
	/// ��ʼ���¼�

	/// @function �߼��߳̿�ʼ����
	/// 
	virtual void LogicThreadInit() /*= 0*/;

	//////////////////////////////////////////////////////////////////////////
	/// ״̬�¼�

	/// @function �����������Ѿ������ɹ�
	/// 
	/// @return �ɹ�����true, ����false��������ֹͣ
	virtual bool OnStarted() /*= 0*/;

	/// @function ����������׼��ֹͣ
	/// 
	virtual void OnReadyStop() /*= 0*/;

	/// @function �������ڵ�ע��ɹ�
	/// 
	/// @param sessionID �ỰId
	/// @param serverId ������id
	/// @param type ����������
	/// @param addr �ڵ��ַ��Ϣ
	virtual void OnNodeRegisterSuccess(uint64_t sessionID, unsigned int serverId, ServerType type, Kernel::CAddress& addr) /*= 0*/;

	//////////////////////////////////////////////////////////////////////////
	/// �Զ����¼�

	/// @function �Լ����ƻ�����
	/// @note �������߳��¼�
	/// 
	/// @param sessionID �Ựid
	/// @param inBuf ����������
	/// @param inLen ���뻺�������ݳ���
	/// @param out �������(�������)(��������)
	/// @param outLen ������󳤶�
	/// @param type ���ƻ���������(0:���ջ���, 1:���ͻ�����)
	/// @return ���ؽ��,�����������İ�����true
	virtual bool OnSelfContorlBuf(uint64_t sessionID, void* inBuf, unsigned int inLen, void* out, unsigned int &outLen, unsigned int type = 0) /*= 0*/;

	/// @function �Զ�������¼�
	/// 
	/// @param eventId �¼�id
	/// @param data ����
	/// @param size ���ݴ�С
	/// @return ���ؽ��
	virtual bool OnSelfContorlEvent(unsigned int eventID, void* data, unsigned short size) /*= 0*/;

	/// @function �Զ������
	/// @note �������߳��¼� send thread
	/// 
	/// @param src ԭ����
	/// @param srcLen ԭ���ݳ���
	/// @param dst ���ܺ�����
	/// @return ���ܺ�����ݳ���
	virtual unsigned int OnSelfEncrypt(const char* src, unsigned int srcLen, char* dst) /*= 0*/;

	/// @function �Զ������
	/// @note �������߳��¼� recv thread
	/// 
	/// @param src ԭ����
	/// @param srcLen ԭ���ݳ���
	/// @param dst ���ܺ�����
	/// @return ���ܺ�����ݳ���
	virtual unsigned int OnSelfDecrypt(const char* src, unsigned int srcLen, char* dst) /*= 0*/;

	//////////////////////////////////////////////////////////////////////////
	/// �����¼�

	/// @function �û����ӳɹ�
	/// 
	/// @param sessionID �ỰID
	/// @param bindID ���ĸ��󶨶˿���������
	/// @param addr ���ӵ�ַ��Ϣ
	/// @return ���ؽ��, ����false����ر��׽���
	virtual bool OnConnect(uint64_t sessionID, unsigned int bindID, const Kernel::CAddress* addr) /*= 0*/;

	/// @function �û�������Ϣ�¼���ȡ
	/// 
	/// @param sessionID �ỰID
	/// @param data ����
	/// @param size ���ݳ���
	/// @param exter ��չֵ
	/// @param addr ���ӵ�ַ��Ϣ
	/// @return ���ؽ��, ����false����ر��׽���
	virtual bool OnReadEvent(uint64_t sessionID, void* data, unsigned short size, uint64_t exter, const Kernel::CAddress* addr) /*= 0*/;

	/// @function ����ر�
	/// 
	/// @param sessionID �ỰID
	/// @param addr ���ӵ�ַ��Ϣ
	virtual void OnCloseEvent(uint64_t sessionID, const Kernel::CAddress* addr)/* = 0*/;

	//////////////////////////////////////////////////////////////////////////
	/// ��ʱ���¼�

	/// @function ��ʱ���¼�
	///
	/// @param timerID ��ʱ��ID
	/// @param interval ʱ����(����Ϊ��λ)
	/// @param overTime ����ʱ��
	/// @param param ��ʱ����������
	/// @param paramLen ��ʱ����������
	/// @return ���ؽ��, ����false�����Ƴ���ʱ��
	virtual bool OnTimerEvent(unsigned int timerID, unsigned int interval, unsigned int overTime, const void* param = NULL, unsigned short paramLen = 0) /*= 0*/;

	//////////////////////////////////////////////////////////////////////////
	/// ���ݿ��¼�

	/// @function ���ݿ���������¼�
	/// @note �������߳��¼� db thread
	/// 
	/// @param sessionID �ỰID(������)
	/// @param requestID ���ݿ�����ID
	/// @param data ����
	/// @param size ��С
	/// @return ���ؽ�� �ɹ�����true,ʧ�ܷ���false
	virtual bool OnDataBaseRequest(uint64_t sessionID, unsigned int requestID, void* data, unsigned short size) /*= 0*/;

	/// @function �����¼�
	/// 
	/// @param sessionID �ỰID(������)
	/// @param dbID ���ݿ�����ID
	/// @param data ����
	/// @param size ��С
	/// @return ���ؽ�� �ɹ�����true,ʧ�ܷ���false
	virtual bool OnDatabaseEvent(uint64_t sessionID, unsigned int dbID, void* data, unsigned short size) /*= 0*/;

	//////////////////////////////////////////////////////////////////////////
	/// ��Ϊweb������ʱ����¼�

	/// @function web�������¼�
	/// @note �������߳��¼� read thread
	/// 
	/// @param httpReq web����
	/// @param httpRes web�ظ�
	/// @return ���ؽ��
	virtual bool OnHttpServerEvent(Kernel::CHttpRequest* httpReq, Kernel::CHttpResponse* httRes) /*= 0*/;

	//////////////////////////////////////////////////////////////////////////
	/// �ֲ�ʽ����

	/// @function ���ش���������
	/// 
	/// @param serviceName ������Ϣ
	/// @param result �������񷵻ؽ��
	virtual void LocalCreateService(string serviceName, int result) /*= 0*/;

	/// @function ����ɾ��������
	/// 
	/// @param result ɾ�����񷵻ؽ��
	virtual void LocalDeleteService(string serviceName, int result) /*= 0*/;

	/// @function ��ѯ����
	/// @note ѡ��������
	///
	/// @param sessionID �Ựid
	/// @param data ����
	/// @param size ����
	/// @return ����Ͷ�ݷ������(Ĭ�����߼����߳�)
	virtual string QueryServiceQueue(uint64_t sessionID, const void* data, unsigned short size) /*= 0*/;

	/// @function Զ�����󴴽�����
	/// 
	/// @param serviceName ������Ϣ
	/// @param result �������񷵻ؽ��
	virtual void RemoteCreateService(string serviceName, uint64_t sessioinID, const Kernel::CAddress* addr) /*= 0*/;

	/// @function Զ������ɾ������
	/// 
	/// @param result ɾ�����񷵻ؽ��
	virtual void RemoteDeleteService(string serviceName, bool result) /*= 0*/;

	/// @function �����������¼�
	/// 
	/// @param sessionID �Ựid
	/// @param func ִ�к���
	/// @param data ����
	/// @param len ����
	virtual void ServiceSendData(uint64_t sessionID, string func, const void* data, unsigned short size, uint64_t exter, const Kernel::CAddress* addr) /*= 0*/;

	/// @function ������������¼�
	/// 
	/// @param sessionID �Ựid
	/// @param func ִ�к���
	/// @param data ����
	/// @param len ����
	/// @return ���ؽ������
	virtual string ServiceCallData(uint64_t sessionID, string func, const void* data, unsigned short size, uint64_t exter, const Kernel::CAddress* addr) /*= 0*/;

public:
	/// @function �����¼����ӿ�
	/// 
	/// @param out �ӿڶ���
	void SetEventOut(IEventOut* out) { m_EventOut = out; }

	/// @function ��ȡ�¼����ӿ�
	/// 
	/// @return �ӿڶ���
	IEventOut* GetEventOut() { return m_EventOut; }

	/// @function �����¼����ӿ�
	/// 
	/// @param out �ӿڶ���
	void SetClientOut(IClientOut* out) { m_ClientOut = out; }

	/// @function ��ȡ�¼����ӿ�
	/// 
	/// @return �ӿڶ���
	IClientOut* GetClientOut() { return m_ClientOut; }

	/// @function ��ʼ��
	/// 
	/// @return ���ؽ��
	bool Init();

	/// @function ��������
	/// 
	/// @param sessionID �ỰID
	/// @param cmd ����
	/// @param buf ����
	/// @param size ����
	/// @return ���ط��ͽ��
	bool Send(uint64_t sessionID, unsigned short cmd, const char* buf, unsigned int size);

#ifdef _OPEN_LUA_MODULE_

	/// @function ���reload�ű�
	/// 
	void ReloadScriptTask();

	/// @function ��ȡ���߼�������
	/// 
	/// @return ���ط�����
	string GetMainLogic() const { return m_MainLogicName; }

#endif 
	
private:
	IEventOut*					m_EventOut;			///<�¼���
	IClientOut*					m_ClientOut;

public:
#ifdef _OPEN_LUA_MODULE_
	CLuaCppManager*				m_LuaCppManager;	/// lua cpp ģ�����
	CLuaCppModule*				m_LogicModule;		/// lua �߼�����ģ��
	CLuaCppModule*				m_DBModule;			/// lua db����ģ��
	//message_queue				m_ReloadScriptMQ;	/// ���¼��ؽű���Ϣ����
	string						m_MainLogicName;	/// ���߼�����
#endif

};


#endif //__ATTEMPER_EVENT_H__