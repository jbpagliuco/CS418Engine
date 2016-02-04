#include <Windows.h>

#include "Engine.h"
#include <stdio.h>

#include "math\Vector.h"
#include "math\Matrix.h"

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








	Vector v1(1.0f, 5.0f, 9.0f, 13.0f);
	Vector v2(2.0f, 6.0f, 10.0f, 14.0f);
	Vector v3(3.0f, 7.0f, 11.0f, 15.0f);
	Vector v4(4.0f, 8.0f, 12.0f, 16.0f);
	Matrix m1(v1, v2, v3, v4);
	
	v1 = Vector(1.0f, 0.0f, 0.0f, 0.0f);
	v2 = Vector(0.0f, 2.0f, 0.0f, 5.0f);
	v3 = Vector(0.0f, 3.0f, 4.0f, 6.0f);
	v4 = Vector(0.0f, 0.0f, 0.0f, 7.0f);
	Matrix m2(v1, v2, v3, v4);

	Matrix result = m1 * m2;
	m2.invert(nullptr);
	printmatrix(m2);
	m2.transpose();
	printmatrix(m2);












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