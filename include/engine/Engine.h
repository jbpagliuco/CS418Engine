#pragma once

#include "graphics/GraphicsManager.h"
#include "content/AssetManager.h"
#include "LuaManager.h"

#include "util/GameTimer.h"

namespace CS418
{
	/* Manages all subsystems of the engine */
	class Engine
	{
	public:
		virtual ~Engine();

		void Initialize();

		int Update();
		void Draw();

	private:
		void readConfigFile(const std::string &file);
		void dispatchKeyAndValue(const std::string &key, const std::string &value);

	private:
		GraphicsManager m_gfx;
		AssetManager m_assetManager;
		LuaManager m_luaManager;

		GameTimer m_gameTimer;
	};
}