#pragma once

#include "graphics/GraphicsManager.h"
#include "Game.h"
#include "content/AssetManager.h"

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
		GraphicsManager m_gfx;
		Game m_game;

		AssetManager m_assetManager;
	};
}