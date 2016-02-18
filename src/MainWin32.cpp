#include <Windows.h>

#include "engine/Engine.h"
#include <stdio.h>

#include "math/Vector.h"
#include "math/Matrix.h"

using namespace CS418;

void printvector(const Vector &v)
{
	printf("(X: %f, Y: %f, Z: %f, W: %f)\n", v.getX(), v.getY(), v.getZ(), v.getW());
}

void printmatrix(const Matrix &m)
{
	for (U8 i = 0; i < 4; i++)
	{
		printf("%f %f %f %f\n", m(i, 0), m(i, 1), m(i, 2), m(i, 3));
	}
	printf("\n");
}

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

		engine.Draw();
	}

	return 0;
}