#include "Types.h"
#ifdef _OPEN_LUA_MODULE_
#ifndef __LUA_CPP_MODULE_H__
#define __LUA_CPP_MODULE_H__

#include "LuaCppDefine.h"
#include "Address.h"

#ifdef __WIN_PLATFORM
#ifdef _DEBUG
#pragma comment(lib, "lua5.1.lib")
#else
#pragma comment(lib, "lua51.lib")
#endif
#pragma comment(lib, "luabind.lib")
#endif

// lua module ֧��
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "luabind/luabind.hpp"
#include "luabind/function.hpp"
#include "luabind/class.hpp"
#include "luabind/object.hpp"
#include "luabind/adopt_policy.hpp"
#include "luabind/container_policy.hpp"
#include "luabind/copy_policy.hpp"
#include "luabind/dependency_policy.hpp"
#include "luabind/discard_result_policy.hpp"
#include "luabind/iterator_policy.hpp"
#include "luabind/out_value_policy.hpp"
#include "luabind/raw_policy.hpp"
#include "luabind/return_reference_to_policy.hpp"
#include "luabind/get_main_thread.hpp"
//#include "luabind/operator.hpp"

// for stl
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>

// lua ����ص�����
extern int PcallbackErrFun(lua_State* L);

using namespace luabind;
using namespace std;

// lua ģ��(note: ����ʹ��luaģ���߼������Ȱ�װlua)
class CLuaCppModule
{
public:
	/// @param serviceName ������
	/// @param sciprtRootPath �ű���Ŀ¼
	/// @param serverRootPath ��ǰ���з������ű���Ŀ¼
	CLuaCppModule(string serviceName, string sciprtRootPath, string serverRootPath);
	~CLuaCppModule();

	/// @function ��ȡlua���������
	/// 
	/// @return ����lua���������
	lua_State* GetLuaState() { return L; }

	/// @function ��ȡ�ű�·��
	/// 
	string GetServerPath() const { return m_ServerRootPath; }

	/// @function ��ʼ��
	/// @note �ӽű��ļ�·���У�����LoadModule.lua, ServerEvent.lua
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Init();

	/// @function ����
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Start();

	/// @function ֹͣ
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Stop();

	/// @function ���¼��ؽű�
	/// 
	/// @return �ɹ�����true, ʧ�ܷ���false
	bool Reload();

	/// @function ���ش���������
	/// 
	/// @param serviceName ������Ϣ
	/// @param result �������񷵻ؽ��
	void LocalCreateService(string serviceName, int result) /*= 0*/;

	/// @function ����ɾ��������
	/// 
	/// @param result ɾ�����񷵻ؽ��
	void LocalDeleteService(string serviceName, int result) /*= 0*/;

	/// @function Զ�����󴴽�����
	/// 
	/// @param serviceName ������Ϣ
	/// @param result �������񷵻ؽ��
	void RemoteCreateService(string serviceName, uint64_t sessioinID, const Kernel::CAddress* addr) /*= 0*/;

	/// @function Զ������ɾ������
	/// 
	/// @param result ɾ�����񷵻ؽ��
	void RemoteDeleteService(string serviceName, bool result) /*= 0*/;

	/// @function ����lua�ļ�
	/// 
	bool LoadFile(const char* fileName);

	/// @function c++ע���࣬������lua
	/// 
	bool RegisterAll();

	/// @funtion ���lua��·��
	/// 
	/// @param path ��·��
	/// @param is_cpath �Ƿ��ǿ⻷��
	void AddPackagePath(string path, bool is_cpath = false);

	/// @function ������������л���
	///
	/// @param key ��
	/// @param val ֵ
	void SetEnv(string key, string val);

	/// @functioin ��ȡ��������
	/// 
	string GetEnv(string key);

	/// @function ת��stl vector list stack queue set ��lua��
	/// @note ˳������
	/// 
	/// @return ���ض���
	template<class T>
	luabind::object& ConvertIndexTable(T stl, luabind::object &obj)
	{
		obj = luabind::newtable(L);
		typename T::iterator it = stl.begin();
		for(int i = 1; it != stl.end(); ++it, ++i)
		{
			obj[i] = *it;
		}
		return obj;
	}

	/// @function ת��stl map��lua��
	/// @note k,v����
	/// 
	/// @return ���ض���
	template<class T>
	luabind::object& ConvertMapTable(T stl, luabind::object &obj)
	{
		obj = luabind::newtable(L);
		typename T::iterator it = stl.begin();
		for( ; it != stl.end(); ++it)
		{
			obj[it->first] = it->second;
		}
		return obj;
	}

private:
	lua_State*		L;					/// lua���������
	string			m_ServiceName;		/// ������
	string			m_ScriptRootPath;	/// �ű���Ŀ¼
	string			m_ServerRootPath;	/// ��������Ŀ¼
	eServiceStatus	m_Status;			/// ״̬

};

#endif // __LUA_CPP_MODULE_H__
#endif // _OPEN_LUA_MODULE_