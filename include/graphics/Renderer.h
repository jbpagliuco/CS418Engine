#pragma once

#include "Scene.h"
#include "FrameBuffer.h"

#define CS418_MAX_SHADOW_LIGHTS 4

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

		virtual void Draw();

		virtual void Resize(U32 width, U32 height);

	private:
		void drawScene(std::vector<GameObject*> gameObjects, CameraComponent* pCamera, std::vector<LightComponent*> lights)const;
		void drawObject(GameObject *pGO, CameraComponent * pCamera, std::vector<LightComponent*> lights, Matrix & mViewProj)const;
		void drawRenderingComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const;
		void drawTerrainComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const;
		void drawSkyboxComponent(CameraComponent * pCamera, Matrix &mViewProj)const;

		void drawSceneFromLight(const std::vector<GameObject*> gameObjects, const Light &light, size_t index);

	private:
		VECTOR4F m_clearColor;

		ShaderProgram m_shadowShader;
		FrameBuffer m_shadowBuffers[CS418_MAX_SHADOW_LIGHTS];

		FrameBuffer m_post;
		bool m_isPostProcessing;
		RenderingComponent m_postRC;

		Scene * m_pScene;
	};
}