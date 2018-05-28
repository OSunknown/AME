#pragma once
#include <vcclr.h> 
#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace AutumnMorningEngine;
class CoreManager
{
private:
	int abc;
	//gcroot<AutumnMorningEngine::MyForm^> mainform;
	static CoreManager* instance_;

public:
	static CoreManager* Getsingleton()
	{
		static CoreManager* instance_ = new CoreManager();
		return instance_;
	}
	void SetInt(int i)
	{
		abc = i;
	}
	int GetInt()
	{
		return abc;
	}
	void Initialize()
	{
		Application::EnableVisualStyles();

		Application::SetCompatibleTextRenderingDefault(false);
		/*AutumnMorningEngine::MyForm ^ form = gcnew AutumnMorningEngine::MyForm;
*/
		/*mainform = form;*/
		
/*
		AutumnMorningEngine::MyForm form;
		form.Show();*/
	}
public:
	 
	 
};