#ifndef __CORRESPOND_EVENT_H__
#define __CORRESPOND_EVENT_H__

#include "IClientIn.h"
#include "IClientOut.h"

#ifdef _OPEN_LUA_MODULE_
#include "LuaCppModule.h"
#endif

/// @Brief �ͻ����¼����ӿ�
class CCorrespondEvent : public IClientIn
{
public:
	CCorrespondEvent();
	~CCorrespondEvent();

	//////////////////////////////////////////////////////////////////////////
	/// �����¼�

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

	/// @function ���ӷ������ɹ�
	/// 
	///	@param sessionID �Ựid
	/// @param addr ���ӵ�ַ��Ϣ
	/// @return ���ؽ��
	virtual bool OnConnected(uint64_t sessionID, const Kernel::CAddress* addr) /*= 0*/;

	/// @function ���ӷ�����ʧ��
	/// 
	///	@param sessionID �ỰID
	/// @param addr ���ӵ�ַ��Ϣ
	/// @return ���ؽ��
	virtual bool OnConnectedFail(uint64_t sessionID, const Kernel::CAddress* addr) /*= 0*/;

	/// @function ��������Ͽ�����
	/// 
	///	@param sessionID �ỰID
	/// @param addr ���ӵ�ַ��Ϣ
	/// @return ���ؽ��
	virtual bool OnDisconnects(uint64_t sessionID, const Kernel::CAddress* addr) /*= 0*/;

	/// @function �û�������Ϣ�¼���ȡ
	/// 
	/// @param sessionID �Ự�û�ID
	/// @param data ����
	/// @param size ���ݳ���
	/// @param exter ��չֵ
	/// @param addr ��ַ��Ϣ
	/// @return ���ؽ��, ����false����ر��׽���
	virtual bool OnReadEvent(uint64_t sessionID, void* data, unsigned short size, uint64_t exter, const Kernel::CAddress* addr) /*= 0*/;

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

	/// @function �������ڵ�ע��ɹ�
	/// 
	/// @param sessionID �ỰId
	/// @param serverId ������id
	/// @param type ����������
	/// @param addr �ڵ��ַ��Ϣ
	virtual void OnNodeRegisterSuccess(uint64_t sessionID, unsigned int serverId, ServerType type, Kernel::CAddress& addr) /*= 0*/;

public:
	/// @function �����¼����ӿ�
	/// 
	/// @param out �ӿڶ���
	void SetEventOut(IClientOut* out) { m_ClientOut = out; }

	/// @function ��ʼ��
	/// 
	/// @return ���ؽ��
	bool Init();

private:
	IClientOut*					m_ClientOut;			///<�¼���

#ifdef _OPEN_LUA_MODULE_
	CLuaCppModule*				m_LogicModule;			/// lua �߼�����ģ��
	string						m_MainLogicName;	/// ���߼�����
#endif
};

#endif //__I_CLIENT_IN_H__