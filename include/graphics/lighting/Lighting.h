#pragma once

#include "math/Vector.h"

namespace CS418
{
	struct PointLight
	{
		VECTOR4F ambient;
		VECTOR4F diffuse;
		VECTOR4F specular;
		VECTOR3F position;
		F32 range;
		VECTOR3F att;
		F32 intensity;
	};
}