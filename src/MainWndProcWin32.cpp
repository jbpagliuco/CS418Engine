#include "MainWndProcWin32.h"

LRESULT CALLBACK CS418::MainWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}
}