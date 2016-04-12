#ifndef _LUA_CLIENT_EVENT_OUT_H__
#define _LUA_CLIENT_EVENT_OUT_H__

#include "IClientOut.h"

/// @Brief lua�ͻ����¼����ӿ�
class CLuaClientEventOut
{
public:
	CLuaClientEventOut(IClientOut* out);
	~CLuaClientEventOut();

	static CLuaClientEventOut& Instance();

	//////////////////////////////////////////////////////////////////////////
	/// �����¼�

	/// @function ���ӷ�����
	/// 
	/// @param sessionID ���(�Ựid)
	/// @param ip ip��ַ
	/// @param port �˿�
	/// @param type �׽�������
	/// @return ���ػỰid
	double Connect(const char* ip, unsigned short port, SocketType type, double sessionID = 0);

	/// @function ���ӷ�����
	/// 
	/// @param sessionID ���(�Ựid)
	/// @param serverAddr ��������ַ��Ϣ
	/// @param type �׽���Э������
	/// @return ���ػỰid
	double Connect(const Kernel::CAddress* serverAddr, double sessionID = 0);

	/// @function ��������
	/// 
	/// @param sessionID �Ựid
	/// @param data ����
	/// @param size ���ݴ�С
	/// @param addr ��ַ��Ϣ(���ΪNULL��Ĭ��ʹ��tcp)(�������udpЭ�飬������д�˲���)
	/// @return ���ؽ��
	bool SendData(double sessionID, const char* buf, unsigned short size);
	bool SendData(double sessionID, const char* buf, unsigned short size, const Kernel::CAddress* addr);
	bool SendData(double sessionID, const char* data, unsigned short size, const Kernel::CAddress* addr = NULL, int level = Kernel::DATA_LEVEL_NORMAL);

	/// @function ��������
	/// 
	/// @param sessionID �Ựid
	/// @param data ����
	/// @para size ���ݴ�С
	/// @return ���ؽ��
	bool SendData(double sessionID, const char* data, unsigned short size, SocketType type);

	/// @function �ر��û�����
	/// 
	/// @param sessionID �Ựid
	void Close(double sessionID);

	/// @function �ж��û�����
	/// 
	/// @param sessionID �Ựid
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
	/// �����¼�

	/// @function �����û����Ựid
	/// 
	void SetUserToSession(double sessionID, double userId);

	/// @function ���ݻỰ��ȡ�û�id
	/// 
	double GetSessionUserID(double sessionID);

	/// @function p2p����
	/// 
	/// @param srcSessionID ԭ�Ựid
	/// @param srcUserID ԭ�û�id
	/// @param desUserID ����p2p��Ŀ���û�id
	/// @param helpHoldIP Э��p2p��������ַ
	/// @param helpHoldPort �˿�
	/// @param type �׽�������
	/// @return ���ؽ�����ɹ�����true��ʧ�ܷ���false
	bool RequestP2P(double srcSessionID, double srcUserID, double desUserID, const char* helpHoldIP, unsigned short helpHoldPort, SocketType helpHoldType = SOCKET_TYPE_TCP);
	bool RequestP2P(double srcSessionID, double srcUserID, double desUserID, const Kernel::CAddress* helpHoldAddr);

	/// @function �����¼����ӿ�
	/// 
	/// @param out �ӿڶ���
	void SetEventOut(IClientOut* out) { m_EventOut = out; }

private:
	IClientOut*			m_EventOut;		///<�������¼����ӿ�

};


#endif //_LUA_CLIENT_EVENT_OUT_H__