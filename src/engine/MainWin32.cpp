#include <Windows.h>

#include "engine/Engine.h"
#include <stdio.h>

#include "engine/MessageHandler.h"

using namespace CS418;

CS418::Engine engine;

LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return engine.MessageHandler(hwnd, msg, wParam, lParam);
}

int main(int argc, char ** argv)
{
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

		engine.Draw();
	}

	return 0;
}

/*
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int nCmdShow)
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

		engine.Draw();
	}

	return 0;
}
*/