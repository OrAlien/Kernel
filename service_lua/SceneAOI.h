#ifndef __SCENE_AOI_H__
#define __SCENE_AOI_H__

#include "ObjectPool.h"
#include "AOI.h"

typedef struct tagAOIEntry
{
	uint64_t	m_UserID;
	float		m_Pos[2];
	int			m_State;
}AOIEntry;

// ����aoi
class CSceneAOI
{
public:
	CSceneAOI(float radius = 0);
	~CSceneAOI();

	/// @function ��ʼ��
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Init(aoi_Callback enter = NULL, aoi_Callback leave = NULL);

	/// @function ����
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Start();

	/// @functioni ֹͣ
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Stop();

	/// @function tick
	/// 
	void Update();

	/// @function ����aoi����
	/// @userid �û�id
	/// @param pos λ��
	/// @return �ɹ�����true
	bool Insert(unsigned int userId, float pos[2], float radius = 0);

	/// @function �Ƴ�aoi����
	/// @userid �û�id
	/// @param pos λ��
	/// @return �ɹ�����true
	bool Remove(unsigned int userId);

private:
	// key: userid
	Kernel::CObjectPoolMap<unsigned int, AOIEntry> m_UserAOIMap;
	aoi_space*		m_AOISpace;
	aoi_Callback	m_EnterCall;
	aoi_Callback	m_LeaveCall;

};

#endif //__SCENE_AOI_H__