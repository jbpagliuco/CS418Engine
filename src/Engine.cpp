#include "Engine.h"

namespace CS418
{
	Engine::~Engine()
	{
		m_game.UnloadContent();
		m_contentManager.UnloadContent();
	}

	void Engine::Initialize()
	{
		m_gfx.Initialize();
		m_game.Initialize();

		m_game.LoadContent(m_contentManager);
	}

	int Engine::Update()
	{
		m_gfx.BeginScene();
		m_gfx.EndScene();

		return 0;
	}
}