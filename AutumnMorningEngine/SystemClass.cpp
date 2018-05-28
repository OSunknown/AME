#include "SystemClass.h"



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

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIconSm = wc.hIcon;
	wc.hInstance = m_hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = MAKEINTRESOURCE(109);
	wc.lpszClassName = m_applicationName;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);


	RegisterClassEx(&wc);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CXSCREEN);

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
		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}


	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName,
		m_applicationName,
		WS_POPUP,//WS_OVERLAPPEDWINDOW,// | WS_DLGFRAME | WS_CLIPCHILDREN | WS_POPUP, // <- 이게 뭔지 모르니 검색할것
		posX, posY, screenWidth, screenHeight,
		GetDesktopWindow(), nullptr, m_hInstance, nullptr);
	//WS_OVERLAPPEDWINDOW : 상단 바 있음 (아이콘, 파일명,최소화,최대화, 종료 버튼 있음)
	//WS_CLIPSIBLINGS :
	//WS_CLIPCHILDREN :
	//WS_POPUP : 상단 바 없어짐
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