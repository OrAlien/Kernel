#ifndef __SERVICE_UNIT_H__
#define __SERVICE_UNIT_H__

#include "ServerKernel.h"
#include "AttemperEvent.h"
#include "IDBPool.h"
#include "CorrespondEvent.h"

/// @Breif ����Ԫ
class CServiceUnit
{
public:
	CServiceUnit(const char* path);
	~CServiceUnit();

	static CServiceUnit& Instance();

	/// @Brief ���������
	/// 
	bool Run();

	/// @function ֹͣ����
	/// 
	bool Stop();

	/// @function ��ȡ�����ļ�·��
	/// 
	/// @return ����·��
	string GetPath() const { return m_Config; }

private:
	enum ServiceUnitState{ SERVICE_UNIT_START, SERVICE_UNIT_STOP };

	ServiceUnitState			m_State;			///<��������Ԫ״̬
	Kernel::CServerKernel*		m_ServerKernel;		///<�������������
	CAttemperEvent*				m_AttemperEvent;	///<�����¼�
	CCorrespondEvent*			m_CorrespondEvent;	///<Э���¼�
	string						m_Config;			///<�����ļ�

};

#endif //__SERVICE_UNIT_H__