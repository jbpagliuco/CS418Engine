#pragma once

#include "GraphicsManager.h"
#include "Game.h"

namespace CS418
{
	/* Manages all subsystems of the engine */
	class System
	{
	public:
		virtual ~System();

		void Initialize();
		int Update();

	private:
		GraphicsManager m_gfx;
		Game m_game;
	};
}