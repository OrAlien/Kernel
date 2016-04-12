#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include "Types.h"

namespace Kernel
{
// web�ظ�
class CHttpResponse
{
public:
	CHttpResponse(uint64_t sessionID)
		:m_SessionID(sessionID)
	{

	}

	~CHttpResponse() { }

	/// @function ��ȡ�Ựid
	/// 
	/// @return ���ػỰid
	uint64_t GetSessionID() const { return m_SessionID; }

private:
	uint64_t		m_SessionID;					// �Ựid

public:
	string			m_Buffer;						// ��ȡ������һ��ֵ����ֵָʾ�Ƿ񻺳�������ڴ�����������Ӧ֮������
	string			m_BufferOutput;					// ��ȡ������һ��ֵ����ֵָʾ�Ƿ񻺳�������ڴ���������ҳ֮������
	string			m_Cache;						// ��ȡ��ҳ�Ļ������(���磬����ʱ�䡢���������úͱ仯����)
	string			m_CacheControl;
	string			m_Charset;						// ��ȡ������������� HTTP �ַ���
	string			m_ClientDisconnectedToken;
	string			m_ContentEncoding;				// ��ȡ������������� HTTP �ַ���
	string			m_ContentType;					// ��ȡ������������� HTTP MIME ����
	string			m_Cookies;						// ��ȡ��Ӧ cookie ����
	string			m_Expires;
	string			m_Filter;
	string			m_HeaderEncoding;				// ��ȡ�����ñ�ʾ��ǰ��ͷ������ı���� Encoding����
	string			m_Headers;						// ��ȡ��Ӧ��ͷ�ļ���
	string			m_HeadersWritten;
	string			m_IsClientConnected;
	string			m_IsRequestBeingRedirected;
	string			m_Output;						// ʵ�ֵ����� HTTP ��Ӧ�����ı����
	string			m_OutputStream;					// ʵ�ֵ����� HTTP ��������Ķ��������
	string			m_RedirectLocation;
	string			m_Status;						// ���÷��ص��ͻ��˵� Status ��
	string			m_StatusCode;					// ��ȡ�����÷��ظ��ͻ��˵������ HTTP ״̬����
	string			m_StatusDescription;			// ��ȡ�����÷��ظ��ͻ��˵������ HTTP ״̬�ַ���
	string			m_SubStatusCode;
	string			m_SupportsAsyncFlush;
	string			m_SuppressContent;				// ��ȡ������ָʾ�Ƿ� HTTP ���ݷ��͵��ͻ��˵�ֵ
	string			m_SuppressFormsAuthenticationRedirect;

}; // end class CHttpResponse

} // end namespace Kernel


#endif //__HTTP_RESPONSE_H__