#ifndef __CONFIG_PARSE_H__
#define __CONFIG_PARSE_H__

#include "Types.h"
#include <boost/unordered_map.hpp>

namespace Kernel
{

/// @brief ����.conf���͵������ļ�
class _KERNEL_EXPORTS CConfigParse
{
public:
	CConfigParse(string path = "");
	~CConfigParse();

	/// @function ��������
	/// 
	/// @param path �����ļ�·��
	/// @return ���ؽ������
	bool Parse(string path);

	/// @function ��ȡ��������
	/// 
	/// @param key ���ü�
	/// @return ������������
	string Get(string key);

	/// @function ��ȡ��������
	/// 
	/// @param key ���ü�
	/// @return ������������
	bool GetBool(string key);

	/// @function ��ȡ��������
	/// 
	/// @param key ���ü�
	/// @return ������������
	short GetShort(string key);

	/// @function ��ȡ��������
	/// 
	/// @param key ���ü�
	/// @return ������������
	int GetInt(string key);

	/// @function ��ȡ��������
	/// 
	/// @param key ���ü�
	/// @return ������������
	long long GetLongLong(string key);

	/// @function ��ȡ��������
	/// 
	/// @param key ���ü�
	/// @return ������������
	double GetDouble(string key);

	/// @function ���
	/// 
	void Print();

private:
	string		m_ConfigPath;		/// �����ļ�·��
	boost::unordered_map<string, string>	m_Datas;	/// ����

};


}

#endif //__CONFIG_PARSE_H__