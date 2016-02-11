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
		VECTOR4F color;
	} Vertex_t;

	const U8 VERTEX_ENABLE_POSITION = (1 << 0);
	const U8 VERTEX_ENABLE_NORMAL = (1 << 1);
	const U8 VERTEX_ENABLE_TEXCOORD = (1 << 2);
	const U8 VERTEX_ENABLE_TANGENT = (1 << 3);
	const U8 VERTEX_ENABLE_COLOR = (1 << 4);

	typedef U32 Index_t;
}