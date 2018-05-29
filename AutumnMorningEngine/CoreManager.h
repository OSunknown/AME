#pragma once
#include <vcclr.h> 
#include "MyForm.h"
class CoreManager
{
	
private:
	int abc;
	gcroot<AutumnMorningEngine::MyForm^> mainform;
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
	void SetForm(gcroot<AutumnMorningEngine::MyForm^>  form)
	{
		mainform = form;
	}
	void GetForm()
	{
		mainform->Show();
	}
	void GetD3DView(int & W, int & H , System::IntPtr & Handle)
	{
		mainform->GetD3DView(W, H, Handle);
	}
	void Initialize()
	{
		
		/*AutumnMorningEngine::MyForm ^ form = gcnew AutumnMorningEngine::MyForm;
*/
		/*mainform = form;*/
		
	}
public:
	 
	 
};