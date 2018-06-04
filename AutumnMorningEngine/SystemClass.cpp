#include "SystemClass.h"
#include "Debug.h"

SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
}


SystemClass::~SystemClass()
{
}

SystemClass::SystemClass(const SystemClass& other)
{

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: // 창을 끌때 메시지가 전달됨.
		PostQuitMessage(0);// 스레드가 종료 요청을 했다는 것을 시스템에 알린다.
		return 0;
	case WM_CLOSE: // 창을 끌때 메시지가 전달됨.
		PostQuitMessage(0);// 스레드가 종료 요청을 했다는 것을 시스템에 알린다.
		return 0;
	default:
		return ApplicationHandle->MessageHandler(hWnd, msg, wParam, lParam);
	}

}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	m_applicationName = L"AutumnMorning Engine";
	m_hInstance = GetModuleHandle(NULL);
	ApplicationHandle = this;
	InitializeWindows(screenWidth, screenHeight);

	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}
	result = m_Input->Initialize(m_hInstance, m_hWnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hWnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hWnd);
	if (!result)
	{
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(m_hWnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	return true;
}
using namespace System;
using namespace System::Runtime::InteropServices;
[DllImport("user32.dll", SetLastError = true)]
IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
[STAThread]
void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	System::IntPtr handle;
	int Wsize, Hsize;
	CoreManager::Getsingleton()->GetD3DView(Wsize, Hsize, handle);

	RegisterClassEx(&wc);

	screenWidth = Wsize;//GetSystemMetrics(SM_CXSCREEN);
	screenHeight = Hsize;// GetSystemMetrics(SM_CXSCREEN);

	DEVMODE dmScreenSettings;
	int posX, posY;
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else
	{
		screenWidth = Wsize;//GetSystemMetrics(SM_CXSCREEN);
		screenHeight = Hsize;// GetSystemMetrics(SM_CXSCREEN);

		posX = 0;//(GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = 0;// (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName,
		m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,//WS_OVERLAPPEDWINDOW,// | WS_DLGFRAME | WS_CLIPCHILDREN | WS_POPUP, // <- 이게 뭔지 모르니 검색할것
		posX, posY, Wsize, Hsize,
		nullptr, nullptr, m_hInstance, nullptr);
	//WS_OVERLAPPEDWINDOW : 상단 바 있음 (아이콘, 파일명,최소화,최대화, 종료 버튼 있음)
	//WS_CLIPSIBLINGS :
	//WS_CLIPCHILDREN :
	//WS_POPUP : 상단 바 없어짐
	SetParent((System::IntPtr) m_hWnd, handle);
	ShowWindow(m_hWnd, SW_SHOW);

	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	ShowCursor(true);

	return;
}

void SystemClass::Shutdown()
{
	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	ShutdownWindows();
	return;
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(true);
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;

	ApplicationHandle = NULL;

	return;

}
//
//void SystemClass::FindFiles(char * centerPath)
//{
//	_finddata_t fd;
//	long handle2;
//	int result = 1;
//	static char *AssetsRoot = ".\\Assets\\";
//	static char *AllFIle = "*.*";
//
//	char FilePath[255] = "", *AllFilePath = "";
//	size_t my_len = strlen(centerPath);
//	printf("%u\n", my_len);
//	if (my_len > 0)
//	{
//		sprintf(FilePath, "%s\\%s", centerPath, AllFIle);
//	}
//	else
//	{
//		sprintf(FilePath, "%s%s", AssetsRoot, AllFIle);
//	}
//	//printf("%s \n",FilePath);
//
//	handle2 = _findfirst(FilePath, &fd);  //현재 폴더 내 모든 파일을 찾는다.
//
//	if (handle2 == -1)
//	{
//		printf("There were no files.\n");
//		return;
//	}
//	char cFilePath[255] = "";
//	// . 과 .. 파일을 넘어가기위해서 
//	result = _findnext(handle2, &fd);
//	result = _findnext(handle2, &fd);
//	while (result != -1)
//	{
//		//printf("%s\n", fd.name);
//		//printf("File: %s FileType :", fd.name);
//
//		if (my_len > 0)
//		{
//			sprintf(cFilePath, "%s\\%s", centerPath, fd.name);
//		}
//		else
//		{
//			sprintf(cFilePath, "%s%s", AssetsRoot, fd.name);
//		}
//
//		int c = isFileOrDir(cFilePath);
//		printf("%s\n", cFilePath);
//		CoreManager::Getsingleton()->AddContextItem(fd.name, c);
//		switch (c)
//		{
//		case 0:
//			/*printf("{\n");
//			FindFiles(cFilePath);
//			printf("}\n");*/
//			break;
//		}
//
//		/*size_t my_len = strlen(fd.name);
//		printf("%u\n", my_len);*/
//		result = _findnext(handle2, &fd);
//	}
//
//	_findclose(handle2);
//}
//
//int SystemClass::isFileOrDir(char * s)
//{
//	_finddatai64_t c_file;
//	intptr_t hFile;
//	int result;
//	char  drive[_MAX_PATH];
//	char  dir[_MAX_PATH];
//	char  fname[_MAX_PATH];
//	char  ext[_MAX_PATH];
//	char fullpath[_MAX_PATH];
//	_fullpath(fullpath, s, _MAX_PATH);
//
//	if ((hFile = _findfirsti64(s, &c_file)) == -1L)
//		result = -1; // 파일 또는 디렉토리가 없으면 -1 반환
//	else
//		if (c_file.attrib & _A_SUBDIR)
//		{
//			result = 0; // 디렉토리면 0 반환
//		}
//		else
//		{
//			_splitpath(fullpath, drive, dir, fname, ext);
//			string str = ext;
//
//			if (str == ".obj" || str == ".OBJ")
//			{
//				result = 1;
//			}
//			else if (str == ".fbx")
//			{
//				result = 2;
//			}
//			else if (str == ".txt")
//			{
//				result = 3;
//			}
//			else if (str == "")
//			{
//				result = 4; 
//			}
//			else
//			{
//				// 그밖의 경우는 "존재하는 파일"이기에 1 반환
//				// 이미지 만들기 전이니까 그냥 1.. 
//				result = 1;
//			}
//			
//		}
//
//
//	_findclose(hFile);
//
//	return result;
//}

void SystemClass::Run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
}

bool SystemClass::Frame()
{
	bool keyDown, result;
	float rotationY;


	// Update the system stats.
	m_Timer->Frame();

	// Do the input frame processing.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(m_Timer->GetTime());

	// Check if the left or right arrow key has been pressed, if so rotate the camera accordingly.
	keyDown = m_Input->IsLeftArrowPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightArrowPressed();
	m_Position->TurnRight(keyDown);

	// Get the current view point rotation.
	m_Position->GetRotation(rotationY);

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame(rotationY);
	if (!result)
	{
		return false;
	}

	// Finally render the graphics to the screen.
	result = m_Graphics->Render();
	if (!result)
	{
		return false;
	}
	return true;
}