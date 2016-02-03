#include "AppWindow.h"

#include "MainWndProcWin32.h"

CS418::WindowHandle CS418::CreateApplicationWindow(const CS418::WINDOW_DESC &wd)
{
	HWND hwnd;

	WNDCLASSEXA wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEXA));
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = CS418::MainWndProc;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
	wc.hIcon = wc.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = wd.caption;
	wc.lpszMenuName = nullptr;
	
	if (!RegisterClassExA(&wc))
	{
		OutputDebugStringA("Failed to register class");
		PostQuitMessage(0);
	}

	hwnd = CreateWindowA(wc.lpszClassName, wd.caption, WS_OVERLAPPEDWINDOW, wd.position.X, wd.position.Y, wd.size.X, wd.size.Y, nullptr, nullptr, wc.hInstance, 0);
	if (!hwnd)
	{
		OutputDebugStringA("Failed to create window");
		PostQuitMessage(0);
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);

	return hwnd;
}