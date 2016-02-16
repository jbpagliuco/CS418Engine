#pragma once

#include "Util.h"
#include <math.h>

namespace CS418
{
	const F32 PI = 3.1415927410125732421875;
	const F32 PI_DIV2 = PI / 2.0f;
	const F32 PI_DIV3 = PI / 3.0f;
	const F32 PI_DIV4 = PI / 4.0f;
	const F32 PI_DIV6 = PI / 6.0f;
	const F32 PI_MUL2 = PI * 2.0f;
	const F32 PI_3DIV2 = 3.0f * PI / 2.0f;

	const F32 FLOAT_EPSILON = 1E-5f;
	const D64 DOUBLE_EPSILON = 1E-9;
	const D64 LONGDOUBLE_EPSILON = DOUBLE_EPSILON;

	bool FEquals(F32 first, F32 second, F32 epsilon = FLOAT_EPSILON);
	bool DEquals(D64 first, D64 second, D64 epsilon = DOUBLE_EPSILON);
}