#include "Engine.h"

namespace CS418
{
	Engine::~Engine()
	{

	}

	void Engine::Initialize()
	{
		m_gfx.Initialize();
		m_game.Initialize();
	}

	int Engine::Update()
	{
		m_gfx.BeginScene();
		m_gfx.EndScene();

		return 0;
	}
}