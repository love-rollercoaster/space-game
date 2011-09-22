#include "Window.h"

Window::Window(string title,  HINSTANCE currentInstance, DWORD style, int width, int height)
	: className("win32app")
{
	initializeWindowClass(currentInstance, style);
	registerWindowClass();
	createWindow(currentInstance, title, width, height);
}

Window::~Window(void)
{
}

void Window::initializeWindowClass(HINSTANCE currentInstance, DWORD style)
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc    = this->WindowProcedure;
	windowClass.cbClsExtra     = 0;
	windowClass.cbWndExtra     = 0;
	windowClass.hInstance      = currentInstance;
	windowClass.hIcon          = LoadIcon(currentInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	windowClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszMenuName   = NULL;
	windowClass.lpszClassName  = className.c_str();
	windowClass.hIconSm        = LoadIcon(currentInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	windowClass.style          = style;
	windowClass.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
}

void Window::registerWindowClass()
{
	if (!RegisterClassEx(&windowClass)) {
		// throw here
	}
}

void Window::createWindow(HINSTANCE currentInstance, string title, int width, int height)
{
	windowHandle = CreateWindow(className.c_str(),
								title.c_str(),
								WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, CW_USEDEFAULT,
								width,
								height,
								NULL,
								NULL,
								currentInstance,
								NULL);
	if (!windowHandle) {
		// throw here
	}
}

LRESULT CALLBACK Window::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR greeting[] = _T("Hello, World!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

WPARAM Window::runMessageLoop()
{
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void Window::show()
{
	ShowWindow(windowHandle, SW_SHOW);
}
