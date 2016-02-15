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
		m_game.Initialize(m_gfx);

		m_game.LoadContent(m_contentManager);
	}

	int Engine::Update()
	{
		return 0;
	}

	void Engine::Draw()
	{
		m_gfx.BeginScene();
		m_gfx.Draw();
		m_gfx.EndScene();
	}
}