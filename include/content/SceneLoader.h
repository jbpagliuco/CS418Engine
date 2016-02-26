#pragma once

#include <string>

#include "graphics/Scene.h"
#include "AssetManager.h"
#include "graphics/GraphicsManager.h"

namespace CS418
{
	extern Scene * LoadScene(AssetManager * assetManager, const std::string &sceneFilepath, LuaManager * pLuaManager, GraphicsManager * pGfxManager);
}