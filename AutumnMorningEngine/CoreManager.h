#pragma once
#include <vcclr.h> 
#include "MyForm.h"
#include "FileManager.h"
class CoreManager
{
	
private:
	int abc;
	gcroot<AutumnMorningEngine::MyForm^> mainform;
//	static CoreManager* instance_;

public:
	static CoreManager* Getsingleton()
	{
		static CoreManager* instance_ = new CoreManager();
		return instance_;
	}
	void Initialize(gcroot<AutumnMorningEngine::MyForm^>  form)
	{
		FileManager::Getsingleton()->initialize();
		mainform = form;
		mainform->Show();
		SetListView();
	}
	void SetInt(int i)
	{
		abc = i;
	}
	int GetInt()
	{
		return abc;
	}
	
	void SetListView()
	{
		mainform->SetListView();
	}
	

	void SetForm(gcroot<AutumnMorningEngine::MyForm^>  form)
	{
		
	}
	void GetForm()
	{
		
	}
	void GetD3DView(int & W, int & H , System::IntPtr & Handle)
	{
		mainform->GetD3DView(W, H, Handle);
	}

public:
	 
	 
};