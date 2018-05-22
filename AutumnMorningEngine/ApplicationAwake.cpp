#include "stdafx.h"
#include "SystemClass.h"


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;

	System = new SystemClass;
	if (!System)
	{
		return 0;
	}
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
	}
	
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}


	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}

