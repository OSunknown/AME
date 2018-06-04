#pragma once
#include <Windows.h>
#include <Commdlg.h>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "FileManager.h"
namespace AutumnMorningEngine {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm1에 대한 요약입니다.
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
			listView1->View = View::LargeIcon;
			listView1->TileSize = System::Drawing::Size(120, 120);
			imageList1 = gcnew ImageList();
			//System::Drawing::Icon("book.ico")
			imageList1->ImageSize = System::Drawing::Size(64, 64);
			imageList1->Images->Add(Image::FromFile(".\\data\\Folder-icon.png"));
			imageList1->Images->Add(Image::FromFile(".\\data\\obj-263.png"));
			imageList1->Images->Add(Image::FromFile(".\\data\\FBX.png"));
			imageList1->Images->Add(Image::FromFile(".\\data\\TXT File.png"));
			imageList1->Images->Add(Image::FromFile(".\\data\\JustFile.png"));
			//imageList1->Images->Add(Image::FromFile("c:\\windows\\FeatherTexture.bmp"));
			listView1->LargeImageList = imageList1;
			listView1->DoubleClick += gcnew System::EventHandler(this, &MyForm::listView1_ItemDoubleClickEvent);
			
		}
		void GetD3DView(int &w, int &h, System::IntPtr &Handle)
		{
			w = panel1->Size.Width;
			h = panel1->Size.Height;
			Handle = panel1->Handle;
		}

		void SetListView()
		{
			FolderData mFd = FileManager::Getsingleton()->GetSeletFolder();
			for (auto it = mFd.mChildPath.begin(); it != mFd.mChildPath.end(); it++) {
				AddListviewItem(it->second.c_str(), mFd.types[it->first]);
			}
		}

		void AddListviewItem(const char * name, int type)
		{
			String^ strNew = gcnew String(name);
			listView1->Items->Add(strNew, type);
		}
	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:




	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  objectToolStripMenuItem;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::Button^  button2;





	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->objectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1258, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->objectToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// objectToolStripMenuItem
			// 
			this->objectToolStripMenuItem->Name = L"objectToolStripMenuItem";
			this->objectToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->objectToolStripMenuItem->Text = L"object";
			this->objectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::objectToolStripMenuItem_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1238, 709);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->listView1);
			this->tabPage1->Controls->Add(this->treeView1);
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1238, 709);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Click += gcnew System::EventHandler(this, &MyForm::tabPage1_Click);
			// 
			// listView1
			// 
			this->listView1->Location = System::Drawing::Point(243, 458);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(730, 218);
			this->listView1->TabIndex = 3;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listView1_SelectedIndexChanged);
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(8, 19);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(229, 402);
			this->treeView1->TabIndex = 1;
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MyForm::treeView1_AfterSelect);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(243, 19);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(730, 402);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(0, 27);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1246, 735);
			this->tabControl1->TabIndex = 0;
			// 
			// imageList1
			// 
			this->imageList1->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->imageList1->ImageSize = System::Drawing::Size(16, 16);
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(243, 427);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(96, 22);
			this->button2->TabIndex = 4;
			this->button2->Text = L"상위폴더로";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1258, 758);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm1";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->tabPage1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm1_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void tabPage1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	}
	private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
	}
	private: System::Void objectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowCursor(true);
		OPENFILENAME OFN;
		char str[300];
		char lpstrFile[MAX_PATH] = "";

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		//OFN.hwndOwner = this->Handle;
		OFN.lpstrFilter = L"dds File(*.dds)\0*.dds\0";
		OFN.lpstrFile = (LPWSTR)lpstrFile;
		OFN.nMaxFile = MAX_PATH;
		OFN.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
		if (GetOpenFileName(&OFN) != 0) {

		}
	}

	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}
	private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

	}

	private: System::Void listView1_ItemDoubleClickEvent(System::Object^  sender, System::EventArgs^ e)
	{
		printf("Click \n");
		ListView^ listview = (ListView^)(sender);

		int i = listView1->SelectedIndices[0];
		String^ s = listView1->Items[i]->Text;
		
		printf("%d :", listView1->Items[i]->ImageIndex);
		printf("%s \n", s);
		//System::Windows::Forms::MessageBox::MessageBox::Show("aaa");
		if (listView1->Items[i]->ImageIndex == 0) //folder
		{
			listview->Clear();
			FileManager::Getsingleton()->ChangePath(msclr::interop::marshal_as<std::string>(s).c_str());
			SetListView();
		}
		if (listView1->Items[i]->ImageIndex == 1) //obj
		{

		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		
		listView1->Clear();
		FolderData mFd = FileManager::Getsingleton()->GetSeletFolder();
		FileManager::Getsingleton()->SetSeletPath(mFd.parentsPath.c_str());
		SetListView();
	}
};
}
