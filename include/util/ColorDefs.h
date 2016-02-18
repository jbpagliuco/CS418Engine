#pragma once

#include "math\Vector.h"
#include <string>

namespace CS418
{
	namespace Colors
	{
		const VECTOR4F Black = VECTOR4F(0.0f, 0.0f, 0.0f, 1.0f);
		const VECTOR4F DarkGrey = VECTOR4F(0.25f, 0.25f, 0.25f, 1.0f);
		const VECTOR4F Grey = VECTOR4F(0.5f, 0.5f, 0.5f, 1.0f);
		const VECTOR4F LightGrey = VECTOR4F(0.75f, 0.75f, 0.75f, 1.0f);
		const VECTOR4F White = VECTOR4F(1.0f, 1.0f, 1.0f, 1.0f);

		const VECTOR4F Red = VECTOR4F(1.0f, 0.0f, 0.0f, 1.0f);
		const VECTOR4F Maroon = VECTOR4F(0.5f, 0.0f, 0.0f, 1.0f);

		const VECTOR4F Green = VECTOR4F(0.0f, 0.5f, 0.0f, 1.0f);
		const VECTOR4F Lime = VECTOR4F(0.0f, 1.0f, 0.0f, 1.0f);
		
		const VECTOR4F Blue = VECTOR4F(0.0f, 0.0f, 1.0f, 1.0f);
		const VECTOR4F Navy = VECTOR4F(0.0f, 0.0f, 0.5f, 1.0f);

		const VECTOR4F Purple = VECTOR4F(0.5f, 0.0f, 0.5f, 1.0f);
		const VECTOR4F Teal = VECTOR4F(0.0f, 0.5f, 0.5f, 1.0f);
		const VECTOR4F Olive = VECTOR4F(0.5f, 0.5f, 0.0f, 1.0f);

		const VECTOR4F Yellow = VECTOR4F(1.0f, 1.0f, 0.0f, 1.0f);
		const VECTOR4F Aqua = VECTOR4F(0.0f, 1.0f, 1.0f, 1.0f);
		const VECTOR4F Fuchsia = VECTOR4F(1.0f, 0.0f, 1.0f, 1.0f);

		const VECTOR4F CornflowerBlue = VECTOR4F(0.396f, 0.612f, .937f, 1.0f);

		VECTOR4F StringToColor(const std::string &color);
	}
}