#pragma once

#include "Scene.h"

namespace CS418
{
	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual void Initialize();
		
		virtual void SetScene(Scene * pScene);

		virtual void Draw()const;

	private:
		Scene * m_pScene;
	};
}