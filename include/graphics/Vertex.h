#pragma once

#include "math/Vector.h"

namespace CS418
{
	typedef struct Vertex_t
	{
		Vertex_t()
		{
			position = VECTOR3F(0.0f, 0.0f, 0.0f);
			normal = VECTOR3F(0.0f, 0.0f, 0.0f);
			texCoord = VECTOR2F(0.0f, 0.0f);
			tangent = VECTOR3F(0.0f, 0.0f, 0.0f);
			color = VECTOR4F(0.0f, 0.0f, 0.0f, 0.0f);
		}

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