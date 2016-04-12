#include <iostream>
#include "ServiceUnit.h"
#include "WindowsService.h"
#include <boost/bind.hpp>
#include "Types.h"

#ifdef __WIN_PLATFORM
//���Զ�λ�������ڴ�й¶ ���ڵ��ļ��;�����һ�У����ڼ�� malloc ������ڴ�
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>

//�ѷ����ڴ����Ϣ�������������Զ�λ����һ�з������ڴ�й¶�����ڼ�� new ������ڴ�
#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

_inline void EnableMemLeakCheck()
{
	//������ڳ����˳�ʱ�Զ����� _CrtDumpMemoryLeaks(),���ڶ���˳����ڵ����.
	//���ֻ��һ���˳�λ�ã������ڳ����˳�֮ǰ���� _CrtDumpMemoryLeaks()
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}
#endif //__WIN_PLATFORM

//#define _WIN_SERIVCE_RUN_

bool Run(const char* path)
{
	CServiceUnit* unit = new CServiceUnit(path);
	if(unit)
		unit->Run();
	_SAFE_DELETE_(unit);
	return true;
}

int main(int argc, char* argv[])
{
#if defined(__WIN_PLATFORM) && defined(_DEBUG)
	EnableMemLeakCheck();
	//_CrtSetBreakAlloc(28428);
#endif //__WIN_PLATFORM

#ifdef __WIN_PLATFORM
#ifdef _WIN_SERIVCE_RUN_
	string config = "";
	if(argc > 2)
		config = argv[2];
	else
		config = "E:\\Kernel\\server\\config\\server_win.conf";
#else
	string config = "";
	if(argc >= 2)
		config = argv[1];
	else
		config = "..\\config\\server_win.conf";
#endif
#else
	string config = "";
	if(argc >= 2)
		config = argv[1];
	else
		config = "/work/Kernel/server/config/server.conf";
#endif

#ifdef __WIN_PLATFORM
#ifdef _WIN_SERIVCE_RUN_
	// �Է���ķ�ʽ����
	TCHAR szServiceName[128] = _T("Server");
	TCHAR szServiceDesc[512] = _T("������");
	InitWinService(szServiceName, boost::bind(&Run, _1), config.c_str(), szServiceDesc);

	if(argc > 1)
	{
		if (strcmp(argv[1], "install") == 0 || strcmp(argv[1], "--install") == 0)  
		{  
			WinInstall();
		}  
		else if(strcmp(argv[1], "uninstall") == 0 || strcmp(argv[1], "--uninstall") == 0)
		{  
			WinUninstall();
		} 
	}
	else
	{
		WinStart();
	}
#else
	Run(config.c_str());
#endif //_WIN_SERIVCE_RUN_
#else
	Run(config.c_str());
#endif //__WIN_PLATFORM

	return 0;
}
