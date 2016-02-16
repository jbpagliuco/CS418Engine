#pragma once

#include "graphics/GraphicsManager.h"
#include "content/AssetManager.h"

namespace CS418
{
	/* Provides functions for initialization and game logic, */
	class Application
	{
	public:
		virtual ~Application() = 0;

	public:
		/* Exits the game */
		void Exit();

		/* Updates the game's clock and calls Update() */
		void Tick();

	protected:
		/* Called once at startup for initialization */
		virtual void Initialize(GraphicsManager &gfxManager) = 0;
		/* Called once at startup for loading content */
		virtual void LoadContent(AssetManager &assetManager) = 0;
		/* Called once at the end for unloading content */
		virtual void UnloadContent() = 0;

		/* Called once every frame */
		virtual void Update() = 0;
	};
}
