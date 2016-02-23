#pragma once

#include "Scene.h"

namespace CS418
{
	class GraphicsManager;

	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual void Initialize(GraphicsManager * gfxManager);
		
		virtual void SetScene(Scene * pScene);

		void SetClearColor(const VECTOR4F &color);
		void SetClearColor(const std::string &color);

		virtual void Draw()const;

	private:
		VECTOR4F m_clearColor;

		Scene * m_pScene;
	};
}