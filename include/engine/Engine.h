#pragma once

#include "graphics/GraphicsManager.h"
#include "content/AssetManager.h"
#include "LuaManager.h"
#include "input/InputManager.h"

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

		LRESULT MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		void readConfigFile(const std::string &file);
		void dispatchKeyAndValue(const std::string &key, const std::string &value);

	private:
		GraphicsManager m_gfx;
		AssetManager m_assetManager;
		LuaManager m_luaManager;
		InputManager m_inputManager;

		GameTimer m_gameTimer;
	};
}