#pragma once

#include <string>

#include "Util.h"
#include "math/Vector.h"
#include "graphics/GraphicsManager.h"
#include "graphics/Viewport.h"

namespace CS418
{
	bool StringToBoolean(const std::string &line);
	F32 StringToFloat(const std::string &line);

	VECTOR2F StringToVector2f(const std::string &line);
	VECTOR3F StringToVector3f(const std::string &line);
	VECTOR4F StringToVector4f(const std::string &line);
	VECTOR4F StringToColor(const std::string &line);

	Viewport StringToViewport(const std::string &line, GraphicsManager * pGfxManager);

	std::vector<std::string> SplitString(std::string s, const std::string &delim);

	/*
	template <typename T>
	T StringToT(const std::string &type, std::string &line)
	{
		if (type == "String")
			return line;
		else if (type == "F32")
			return StringToFloat(line);
		else if (type == "Boolean")
			return StringToBoolean(line);
		else if (type == "Vector2f")
			return StringToVector2f(line);
		else if (type == "Vector3f")
			return StringToVector3f(line);
		else if (type == "Vector4f")
			return StringToVector4f(line);
		else if (type == "Color")
			return StringToColor(line);
	}
	*/
}