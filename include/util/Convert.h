#pragma once

#include <string>

#include "Util.h"

#include "content/AssetManager.h"
#include "graphics/GraphicsManager.h"

namespace CS418
{
	struct VECTOR2F;
	struct VECTOR3F;
	struct VECTOR4F;
	class Quaternion;
	struct Viewport;
	class Texture2DGL;
	class TextureCube;
	class Mesh;

	bool StringToBoolean(const std::string &line);
	F32 StringToFloat(const std::string &line);

	VECTOR2F StringToVector2f(const std::string &line);
	VECTOR3F StringToVector3f(const std::string &line);
	VECTOR4F StringToVector4f(const std::string &line);
	Quaternion StringToQuaternion(const std::string &line);
	VECTOR4F StringToColor(const std::string &line);

	Viewport StringToViewport(const std::string &line, GraphicsManager * pGfxManager);

	Mesh StringToMesh(const std::string &line, std::string args);

	Texture2DGL StringToTexture2D(const std::string &line, AssetManager * pAM);
	TextureCube StringToTextureCube(const std::string &line, AssetManager * pAM);

	std::string StringWithoutArray(const std::string &s);
	U32 StringArrayIndex(const std::string &s);
}