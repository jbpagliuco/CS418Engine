#include <Windows.h>

#include "System.h"
#include <stdio.h>

int main(int argc, char ** argv)
{
	CS418::System system;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	system.Initialize();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		system.Update();
	}

	return 0;
}