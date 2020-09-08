#include "System.h"
#include "Utils.h"
#include <string>

System* System::_pInstance = nullptr;

System* System::Instance()
{
	if (_pInstance == nullptr)
		_pInstance = new System();

	return _pInstance;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

bool System::init()
{
	if (_isInitialized) return true;

	if (!createWindow()) return false;

	if (!initHighFrequencyTimer()) return false;

	m_pGfx = new GfxSystem();
	if (!m_pGfx->init(_screenWidth, _screenHeight, m_hWnd)) return false;

	_isInitialized = true;

	return true;
}

void System::run()
{
	while (runWindow() && m_pGfx != nullptr)
	{
		updateHighFrequencyTimer();

		m_pGfx->updateFrame(_deltaTime);
		m_pGfx->renderFrame();
	}
}

void System::deInit()
{
	safeDeInit<GfxSystem>(m_pGfx);

	shutdownWindow();
}

bool System::createWindow()
{
	// Step 1: declare window class
	WNDCLASS wc = {};
	wc.cbClsExtra = 0; // extra memory for class object
	wc.cbWndExtra = 0; // extra memory for window instance
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)); // handle to background brush
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // application cursor, could be null
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // application icon, could be null
	wc.hInstance = GetModuleHandle(nullptr); // handle to application instance
	wc.lpfnWndProc = WndProc; // pointer to window proc, function for windows to communicate with application
	wc.lpszClassName = TEXT("Ultimate DirectX Project"); // class name for window class
	wc.lpszMenuName = nullptr; // class name for menu class
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // behaviour of window

												   // Step 2: register window class
	ATOM wID = RegisterClass(&wc);
	if (wID <= 0) return false;

	// Step 3 (optional): calculate window size and position
	// set client area
	int clientWidth = _screenWidth;
	int clientHeight = _screenHeight;

	// get display size
	int x = (GetSystemMetrics(SM_CXSCREEN) - clientWidth) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - clientHeight) / 2;

	RECT winRect = { x, y, x + clientWidth, y + clientHeight };
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&winRect, style, false);

	// Step 4: create window
	m_hWnd = CreateWindow(
		wc.lpszClassName, // class name for window class
		wc.lpszClassName, // window title
		style, // window style (https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx)
		winRect.left, winRect.top, // window position (original in left top corner)
		winRect.right - winRect.left, winRect.bottom - winRect.top, // window size
		nullptr, // handle to parent window, null for main window
		nullptr, // handle to menu class, null for no menu
		wc.hInstance, // handle to application
		nullptr // optional: additional parameter
		);
	if (m_hWnd == nullptr) return false;

	// Step 5: show window, set foreground and focus
	ShowWindow(m_hWnd, SW_SHOW); // show window with viewing option
	SetForegroundWindow(m_hWnd); // set window to foreground
	SetFocus(m_hWnd); // set keyboard focus on window

	return true;
}

bool System::runWindow()
{
	static MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
		return false;

	return true;
}

void System::shutdownWindow()
{

}

bool System::initHighFrequencyTimer()
{
	LARGE_INTEGER freq; 
	QueryPerformanceFrequency(&freq);

	_secondsPerTick = 1.0f / freq.QuadPart;

	QueryPerformanceCounter(&_lastTickCount);
		
	return true;
}

void System::updateHighFrequencyTimer()
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter(&ticks);

	_deltaTime = _secondsPerTick * (ticks.QuadPart - _lastTickCount.QuadPart);
	_lastTickCount = ticks;

	_frames++;
	_timeSinceLastFrameUpdate += _deltaTime;
	if (_timeSinceLastFrameUpdate >= 1.0f)
	{
		OutputDebugString((TEXT("fps: ") + std::to_wstring(_frames) + TEXT("\n")).c_str());
		_frames = 0;
		_timeSinceLastFrameUpdate -= 1.0f;
	}

	OutputDebugString((std::to_wstring(_deltaTime) + TEXT("\n")).c_str());
	OutputDebugString((TEXT("fps: ") + std::to_wstring(1.0f / _deltaTime) + TEXT("\n")).c_str());
}
