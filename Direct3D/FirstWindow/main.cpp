#include <Windows.h>

LRESULT CALLBACK WndProc(
	HWND hWnd, // handle to window instance
	UINT msg, // message type
	WPARAM wParam, // main information (e.g. virtual key code)
	LPARAM lParam // additonal information (e.g. special key)
)
{
	switch (msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance, // handle to our own application
	HINSTANCE hPrevInstance, // deprecated
	LPSTR szCmdline, // command line
	int iShow // how to run the application window? normal, minimised, maximised
)
{
	// 1. describing the window class
	WNDCLASS wc = {};
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND); // system color
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)); // solid color
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // load system arrow cursor
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // load system application icon
	wc.lpszClassName = TEXT("First Window"); // class name
	wc.hInstance = hInstance; // handle to application instance this window is assosiated to 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // window behavior
	wc.lpfnWndProc = WndProc; // function for communication with operating system

	// 2. register the window class
	if (RegisterClass(&wc) == 0) return -10;

	// 3. (optional) calcualte window rect
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	RECT rect = {0, 0, 640, 480};
	rect.left = halfWidth - rect.right / 2;
	rect.top = halfHeight - rect.bottom / 2;
	rect.right += rect.left;
	rect.bottom += rect.top;
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&rect, style, false);

	// 4. create a window instance 
	HWND hWnd = CreateWindow(
		wc.lpszClassName, // class name
		wc.lpszClassName, // window title
		style, // window style (visual)
		rect.left, rect.top, // window position
		rect.right - rect.left, rect.bottom - rect.top, // window size
		nullptr, // handle to parent window
		nullptr, // handle to menu instance
		hInstance, // handle to application instance
		nullptr, // optional parameters
		);

	if (!hWnd) return -11;

	// 5. show the window & set the focus
	ShowWindow(hWnd, iShow);
	SetFocus(hWnd);

	// 6. run the window
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(10);
	}

	return 0;
}