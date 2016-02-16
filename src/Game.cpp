#include "Game.h"

#include "graphics/RenderingComponent.h"

namespace CS418
{
	Game::~Game()
	{

	}

	void Game::Initialize(GraphicsManager & gfxManager)
	{

	}

	void Game::LoadContent(AssetManager & assetManager)
	{
		assetManager.LoadScene("assets/scene.cs418scene");
	}

	void Game::UnloadContent()
	{

	}

	void Game::Update()
	{

	}
}