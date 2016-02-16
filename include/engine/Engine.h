#pragma once

#include "GraphicsManager.h"
#include "Game.h"
#include "content\ContentManager.h"

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

		ContentManager m_contentManager;
	};
}