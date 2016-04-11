#pragma once

#include "math/Quaternion.h"
#include "util/ColorDefs.h"
#include "graphics/Viewport.h"
#include "graphics/Texture2DGL.h"
#include "graphics/TextureCube.h"

#include "content/AssetManager.h"
#include "graphics/GraphicsManager.h"

namespace CS418
{
	bool StringToBoolean(const std::string &line);
	F32 StringToFloat(const std::string &line);

	VECTOR2F StringToVector2f(const std::string &line);
	VECTOR3F StringToVector3f(const std::string &line);
	VECTOR4F StringToVector4f(const std::string &line);
	Quaternion StringToQuaternion(const std::string &line);
	VECTOR4F StringToColor(const std::string &line);

	Viewport StringToViewport(const std::string &line, GraphicsManager * pGfxManager);

	Texture2DGL StringToTexture2D(const std::string &line, AssetManager * pAM);
	TextureCube StringToTextureCube(const std::string &line,  AssetManager * pAM);

	std::vector<std::string> SplitString(std::string s, const std::string &delim);
}