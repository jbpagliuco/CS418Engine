#pragma once

#include "Application.h"

namespace CS418
{
	class Game : public Application
	{
	public:
		~Game();

		/* Called once at startup for initialization */
		void Initialize();
		/* Called once at startup for loading content */
		void LoadContent();
		/* Called once at the end for unloading content */
		void UnloadContent();

		/* Called once every frame */
		void Update();
	};
}