#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <map>
#include "Types.h"

namespace Kernel
{
// web����
class CHttpRequest
{
public:
	CHttpRequest(uint64_t sessionID, void* pSession)
		:m_SessionID(sessionID)
		,m_SeessionObj(pSession)
	{

	}

	~CHttpRequest() { }

	/// @function ��ȡ�Ựid
	/// 
	/// @return ���ػỰid
	uint64_t GetSessionID() const { return m_SessionID; }

	/// @function ��ȡ�Ự����
	/// 
	/// @return ���ػỰ����
	void* GetSessionObj() { return m_SeessionObj; }

private:
	uint64_t		m_SessionID;		// �ỰId
	void*			m_SeessionObj;		// �Ự����

public:
	string			m_AcceptType;				// ��ȡ�ͻ���֧�ֵ� MIME ��������			
	string			m_AnonymousID;
	string			m_ApplicationPath;			// ��ȡ��������Ӧ�ó��������Ӧ�ó����·����
	string			m_AppRelativeCurrentExecutionFilePath;
	string			m_Browser;
	string			m_ClientCertificate;		// ��ȡ��ǰ����Ŀͻ��˰�ȫ֤��
	string			m_ContentEncoding;			// ��ȡ������ʵ��������ַ���
	string			m_ContentLength;			// ָ���ͻ��˷��͵����ݳ��ȣ����ֽڼƣ�
	string			m_ContentType;				// ��ȡ�����ô�������� MIME ��������
	string			m_Cookies;					// ��ȡ�ͻ��˷��͵� Cookie �ļ���
	string			m_CurrentExecutionFilePath;
	string			m_FilePath;
	string			m_Files;
	string			m_Filter;
	string			m_Form;
	string			m_HttpMethod;				// ��ȡ�ͻ���ʹ�õ� HTTP ���ݴ��䷽������ GET��POST �� HEAD��
	string			m_InputStream;				// ��ȡ����� HTTP ʵ�����������
	string			m_IsAuthenticated;
	string			m_IsLocal;
	string			m_IsSecureConnection;
	string			m_Item;
	string			m_LogonUserIdentity;
	string			m_Params;
	string			m_Path;
	string			m_PathInfo;
	string			m_PhysicalApplicationPath;
	string			m_PhysicalPath;
	string			m_QueryString;
	string			m_RawUrl;
	string			m_RequestType;				// ��ȡ�����ÿͻ���ʹ�õ� HTTP ���ݴ��䷽����GET �� POST��
	string			m_ServerVariables;
	string			m_TotalBytes;				// ��ȡ��ǰ�������е��ֽ���
	string			m_Url;						// ��ȡ�йص�ǰ����� URL ����Ϣ
	string			m_UrlReferrer;
	string			m_UserAgent;				// ��ȡ�ͻ����������ԭʼ�û�������Ϣ
	string			m_UserHostAddress;			// ��ȡԶ�̿ͻ��˵� IP ������ַ
	string			m_UserHostName;				// ��ȡԶ�̿ͻ��˵� DNS ����
	string			m_UserLanguages;			// ��ȡ�ͻ���������ѡ��

	typedef std::map<string, string> WebHeaderMap;
	typedef WebHeaderMap::iterator HeadIt;
	WebHeaderMap	m_Headers;					// ��ȡ HTTP ͷ����
	string			m_TmpHeadKey;
	string			m_TmpHeadValue;

}; // end class CHttpRequest

} // end namespace Kernel


#endif //__HTTP_REQUEST_H__