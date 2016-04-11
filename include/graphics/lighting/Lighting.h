#pragma once

#include "math/Vector.h"

namespace CS418
{
	const U32 LIGHT_TYPE_PARALLEL = 0x00;
	const U32 LIGHT_TYPE_POINT = 0x01;
	const U32 LIGHT_TYPE_SPOTLIGHT = 0x02;

	struct Light
	{
		VECTOR4F ambient;
		VECTOR4F diffuse;
		VECTOR4F specular;
		VECTOR3F position;
		F32 range;
		VECTOR3F direction;
		F32 intensity;
		VECTOR3F att;
		U32 type;
	};
}