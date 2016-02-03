#pragma once

#include "GraphicsManager.h"
#include "Game.h"

namespace CS418
{
	/* Manages all subsystems of the engine */
	class Engine
	{
	public:
		virtual ~Engine();

		void Initialize();
		int Update();

	private:
		GraphicsManager m_gfx;
		Game m_game;
	};
}