#pragma once

#include "math\Vector.h"

namespace CS418
{
	typedef struct Vertex_t
	{
		VECTOR3F position;
		VECTOR3F normal;
		VECTOR2F texCoord;
		VECTOR3F tangent;
	} Vertex_t;

	typedef U32 Index_t;
}