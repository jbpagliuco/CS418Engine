#pragma once

#include "engine/Application.h"
#include "content/AssetManager.h"
#include "graphics/Scene.h"

#include <vector>

namespace CS418
{
	class Game : public Application
	{
	public:
		~Game();

		/* Called once at startup for initialization */
		void Initialize(GraphicsManager &gfxManager);
		/* Called once at startup for loading content */
		void LoadContent(AssetManager &assetManager);
		/* Called once at the end for unloading content */
		void UnloadContent();

		/* Called once every frame */
		void Update();

	private:
		Scene m_scene;
		std::vector<GameObject> m_gameObjects;
	};
}