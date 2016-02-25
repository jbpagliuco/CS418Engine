#pragma once

#include <string>

#include "graphics/Scene.h"
#include "AssetManager.h"

namespace CS418
{
	extern Scene * LoadScene(AssetManager * assetManager, const std::string &sceneFilepath, LuaManager * pLuaManager);
}