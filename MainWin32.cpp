#include <Windows.h>

#include "Engine.h"
#include <stdio.h>

int main(int argc, char ** argv)
{
	CS418::Engine engine;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	engine.Initialize();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		engine.Update();
	}

	return 0;
}