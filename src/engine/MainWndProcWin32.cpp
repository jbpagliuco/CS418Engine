#include "engine/MainWndProcWin32.h"

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

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lparam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lparam)->ptMinTrackSize.y = 200;
		break;

	case WM_SIZE:

		break;

	default:
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}

	return 0;
}