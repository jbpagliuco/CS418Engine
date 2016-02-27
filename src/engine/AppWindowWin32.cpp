#include "engine/AppWindow.h"

#include "engine/MessageHandler.h"

CS418::WindowHandle CS418::CreateApplicationWindow(const CS418::WINDOW_DESC &wd, Engine * pEngine)
{
	HWND hwnd;

	WNDCLASSEXA wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEXA));
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = MessageHandler;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
	wc.hIcon = wc.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = wd.caption;
	wc.lpszMenuName = nullptr;
	
	if (!RegisterClassExA(&wc))
	{
		DWORD error = GetLastError();
		OutputDebugStringA("Failed to register class!\n");
		PostQuitMessage(0);
	}

	hwnd = CreateWindowA(wc.lpszClassName, wd.caption, WS_OVERLAPPEDWINDOW, wd.position.X, wd.position.Y, wd.size.X, wd.size.Y, nullptr, nullptr, wc.hInstance, 0);
	if (!hwnd)
	{
		OutputDebugStringA("Failed to create window!\n");
		PostQuitMessage(0);
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);

	return hwnd;
}