#pragma once

#include "Scene.h"
#include "FrameBuffer.h"

namespace CS418
{
	class AssetManager;
	class GraphicsManager;

	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual void Initialize(GraphicsManager * gfxManager, AssetManager * pAM);
		
		virtual void SetScene(Scene * pScene);

		void SetClearColor(const VECTOR4F &color);
		void SetClearColor(const std::string &color);

		virtual void Draw()const;

		virtual void Resize(U32 width, U32 height);

	private:
		void drawScene(std::vector<GameObject*> gameObjects, std::vector<CameraComponent*> pCameras, std::vector<LightComponent*> lights)const;
		void drawObject(GameObject *pGO, CameraComponent * pCamera, std::vector<LightComponent*> lights, Matrix & mViewProj)const;
		void drawRenderingComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const;
		void drawTerrainComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const;
		void drawSkyboxComponent(CameraComponent * pCamera, Matrix &mViewProj)const;

	private:
		VECTOR4F m_clearColor;

		FrameBuffer m_post;
		bool m_isPostProcessing;
		RenderingComponent m_postRC;

		Scene * m_pScene;
	};
}