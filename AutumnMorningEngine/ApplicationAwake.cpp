#include "stdafx.h"
#include "SystemClass.h"
#include "MyForm.h"
#include "CoreManager.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace AutumnMorningEngine;
[STAThreadAttribute]
void main() 
{
	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	AutumnMorningEngine::MyForm ^ form = gcnew AutumnMorningEngine::MyForm;
	

	CoreManager::Getsingleton()->SetInt(15);
	CoreManager::Getsingleton()->SetForm(form);
	CoreManager::Getsingleton()->GetForm();
	SystemClass* System;
	bool result;
	
	
	System = new SystemClass;
	if (!System)
	{
		return;
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

	return;
}

//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
//{
//	SystemClass* System;
//	bool result;
//
//	System = new SystemClass;
//	if (!System)
//	{
//		return 0;
//	}
//	if (AllocConsole())
//	{
//		freopen("CONOUT$", "w", stdout);
//	}
//	
//	result = System->Initialize();
//	if (result)
//	{
//		System->Run();
//	}
//
//
//	System->Shutdown();
//	delete System;
//	System = 0;
//
//	return 0;
//}

