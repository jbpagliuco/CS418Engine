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

		virtual void Resize(U32 width, U32 height);

	private:
		void drawScene(std::vector<GameObject*> gameObjects, CameraComponent * pCamera, std::vector<LightComponent*> lights)const;
		void drawRenderingComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const;
		void drawTerrainComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const;
		void drawSkyboxComponent(CameraComponent * pCamera, Matrix &mViewProj)const;

	private:
		VECTOR4F m_clearColor;

		Scene * m_pScene;
	};
}