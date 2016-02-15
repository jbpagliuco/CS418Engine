#pragma once

#include "Application.h"
#include "content\ContentManager.h"
#include "Scene.h"

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
		void LoadContent(ContentManager &contentManager);
		/* Called once at the end for unloading content */
		void UnloadContent();

		/* Called once every frame */
		void Update();

	private:
		Scene m_scene;
		std::vector<GameObject> m_gameObjects;
	};
}