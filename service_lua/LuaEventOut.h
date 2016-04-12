#ifndef _LUA_EVENT_OUT_H__
#define _LUA_EVENT_OUT_H__

#include "IEventOut.h"
#include <list>

/// @brief lua�����¼���
class CLuaEventOut
{
public:
	CLuaEventOut(IEventOut* out);
	~CLuaEventOut();

	static CLuaEventOut& Instance();

	//////////////////////////////////////////////////////////////////////////
	/// �����¼�

	/// @function �������׽���
	/// 
	/// @param addr ���ӵ�ַ��Ϣ
	/// @param bindAddr �󶨵�ַ��Ϣ
	/// @param bindID �󶨱�ʶ(�󶨶���˿�ʱ��bindID���벻һ��, 0: �Զ�����)
	/// @param sync ͬ��or�첽
	/// @return �ɹ����ذ󶨱�ʶ��ʧ�ܷ���-1
	int CreateBindSocket(Kernel::CAddress addr, int bindID = 0, bool sync = true);
	int CreateBindSocket(const char* addr, unsigned short port, int bindID = 0, bool sync = true);

	/// @function ɾ�����׽���
	/// 
	/// @param bindID �󶨱�ʶ
	/// @param sync ͬ��or�첽
	/// @return �ɹ�����true
	bool DestoryBindSocket(unsigned int bindID = 0, bool sync = true);

	/// @function �����û����Ựid
	/// 
	void SetUserToSession(double sessionID, double userId);

	/// @function ���ݻỰ��ȡ�û�id
	/// 
	double GetSessionUserID(double sessionID);

	//////////////////////////////////////////////////////////////////////////
	/// �����¼�

	/// @function ��������
	/// 
	/// @param sessionID �ỰID
	/// @param buf ����
	/// @param size ����
	/// @return ���ط��ͽ��
	bool Send(double sessionID, const char* buf, unsigned int size);
	bool Send(double sessionID, const char* buf, unsigned int size, const Kernel::CAddress* addr);
	bool Send(double sessionID, const char* buf, unsigned int size, const Kernel::CAddress* addr = NULL, int level = Kernel::DATA_LEVEL_NORMAL);

	/// @function �㲥����
	/// 
	/// @param buf ����
	/// @param size ����
	/// @param sessionIdList �������ݸ�ָ����һ���û�(std::list<uint64_t>)
	void Broadcast(const char* buf, unsigned int size);
	void Broadcast(const char* buf, unsigned int size, const std::list<double>& sessionIdList);

	/// @function �ر��û�����
	/// 
	/// @param sessionID �ỰID
	void Close(double sessionID);

	/// @function �ж��û�����
	/// 
	/// @param sessionID �ỰID
	void Shutdown(double sessionID);

	//////////////////////////////////////////////////////////////////////////
	/// ��ʱ���¼�

	/// @function ���ö�ʱ��
	/// 
	/// @param timerID ��ʱ�����(�������10)
	/// @param interval ��ʱ�����г�������
	/// @param overTimer ÿ�ֵ���ʱ��(����Ϊ��λ)
	/// @param param ����
	/// @param size �������ݳ���
	/// @return ���ؽ�����ɹ�����true��ʧ�ܷ���false
	bool SetTimer(unsigned int timerID, unsigned int interval, unsigned int overTime);
	bool SetTimer(unsigned int timerID, unsigned int interval, unsigned int overTime, const char* param = NULL, unsigned short size = 0);

	/// @function �Ƴ���ʱ��
	/// 
	/// @parma timerID ��ʱ�����
	/// @return ���ؽ��
	bool KillTimer(unsigned int timerID);

	//////////////////////////////////////////////////////////////////////////
	/// ���ݿ��¼�

	/// @function Ͷ�����ݿ��������
	/// 
	/// @param sessionID �ỰID(������)
	/// @param requestID ���ݿ�����ID
	/// @param data ����
	/// @param size ��С
	/// @param exter ��չֵ
	/// @param ����Ͷ�ݽ��
	bool PostDatabaseRequest(double sessionID, unsigned int requestID, const char* data, unsigned short size, double exter = 0);

	/// @function Ͷ�����ݿ��¼����
	/// 
	/// @param sessionID �ỰID(������)
	/// @param dbID ���ݿ�����ID
	/// @param data ����
	/// @param size ��С
	/// @param local �Ƿ񱾵ش���
	/// @param exter ��չֵ
	/// @param ����Ͷ�ݽ��
	bool PostDatabaseEvent(double sessionID, unsigned int dbID, const char* data, unsigned short size, bool IsLocal = true, double exter = 0);

	//////////////////////////////////////////////////////////////////////////
	/// �Զ����¼�

	/// @function �Զ�������¼�
	/// 
	/// @param eventId �¼�id
	/// @param data ����
	/// @param size ���ݴ�С
	/// @return ���ؽ��
	bool PostSelfEvent(unsigned int eventID, const char* data, unsigned short size);

	/// @function �����¼����ӿ�
	/// 
	/// @param out �ӿڶ���
	void SetEventOut(IEventOut* out) { m_EventOut = out; }

private:
	IEventOut*			m_EventOut;		///<�������¼����ӿ�

};

#endif //_LUA_EVENT_OUT_H__