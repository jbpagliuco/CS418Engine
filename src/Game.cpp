#include "Game.h"

#include "graphics\RenderingComponent.h"

namespace CS418
{
	Game::~Game()
	{

	}

	void Game::Initialize(GraphicsManager & gfxManager)
	{
		gfxManager.SetScene(&m_scene);
	}

	void Game::LoadContent(ContentManager & contentManager)
	{
		Mesh * pMeshTriangle = contentManager.LoadMesh("assets\\triangle.obj");
		ShaderProgram * pBasicShader = contentManager.LoadShader("assets\\vertexShader.vert", "assets\\fragShader.frag");
		Material material;
		material.Initialize(pBasicShader);

		RenderingComponent *rendComp = new RenderingComponent;
		rendComp->Initialize(pMeshTriangle, material);
		
		GameObject gameObject("Game Object");
		gameObject.AddComponent(rendComp);

		m_gameObjects.push_back(gameObject);
		m_scene.AddGameObject(&m_gameObjects.at(0));
	}

	void Game::UnloadContent()
	{

	}

	void Game::Update()
	{

	}
}