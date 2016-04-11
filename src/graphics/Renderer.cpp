#include "graphics/Renderer.h"

#include <GL/glew.h>

#include "graphics/GraphicsManager.h"
#include "components/RenderingComponent.h"
#include "components/TerrainComponent.h"

#include "util/ColorDefs.h"
#include <Windows.h>

namespace CS418
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(GraphicsManager * gfxManager)
	{
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPointSize(4.0f);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
		glEnable(GL_DEPTH);
		glDepthFunc(GL_LESS);

		glewInit();

		Vector2<U32> dim = gfxManager->GetWindowDimensions();
		glViewport(0, 0, dim.X, dim.Y);
	}

	void Renderer::SetScene(Scene * pScene)
	{
		m_pScene = pScene;
	}

	void Renderer::SetClearColor(const VECTOR4F &color)
	{
		m_clearColor = color;
		glClearColor(color.x, color.y, color.z, color.w);
	}
	void Renderer::SetClearColor(const std::string &color)
	{
		m_clearColor= Colors::StringToColor(color);
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
	}

	void Renderer::Resize(U32 width, U32 height)
	{
		if (m_pScene)
		{
			std::vector<CameraComponent*> pCameras = m_pScene->GetCameras();
			for (std::vector<CameraComponent*>::const_iterator camera = pCameras.begin(); camera != pCameras.end(); camera++)
			{
				(*camera)->Resize(width, height);
			}
		}
	}

	void Renderer::Draw()const
	{
		if (m_pScene)
		{
			// Reset scene
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LESS);
			glCullFace(GL_BACK);

			const std::vector<GameObject*> gameObjects = m_pScene->GetVisibleGameObjects();
			const std::vector<LightComponent*> lights = m_pScene->GetLights();

			std::vector<CameraComponent*> pCameras = m_pScene->GetCameras();
			for (std::vector<CameraComponent*>::const_iterator camera = pCameras.begin(); camera != pCameras.end(); camera++)
			{
				if ((*camera)->Enabled)
				{
					Viewport vp = (*camera)->GetViewport();
					glViewport((I32)vp.TopLeftX, (I32)vp.TopLeftY, (U32)vp.Width, (U32)vp.Height);

					glClear(GL_DEPTH_BUFFER_BIT);

					drawScene(gameObjects, (*camera), lights);
				}
			}
		}
	}

	void Renderer::drawScene(std::vector<GameObject*> gameObjects, CameraComponent * pCamera, std::vector<LightComponent*> lights)const
	{
		Matrix mViewProj = pCamera->buildMatrix();

		for (std::vector<GameObject*>::const_iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
		{
			drawRenderingComponents((*gameObject), pCamera, mViewProj, lights);
			drawTerrainComponents((*gameObject), pCamera, mViewProj, lights);
		}

		drawSkyboxComponent(pCamera, mViewProj);
	}

	void Renderer::drawRenderingComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const
	{
		const std::vector<RenderingComponent*> &renderables = pGO->GetComponentsOfType<RenderingComponent>("RenderingComponent");

		for (std::vector<RenderingComponent*>::const_iterator renderable = renderables.begin(); renderable != renderables.end(); renderable++)
		{
			RenderingComponent *pRC = (*renderable);
			glUseProgram(pRC->m_material.GetShaderProgram()->m_shaderProgram);

			Matrix m = pGO->GetTransform()->CreateWorldMatrix();

			Matrix wvp = mViewProj * m;
			pRC->m_material.SetMatrix4x4("_WVP", wvp);
			pRC->m_material.SetMatrix4x4("_World", m);
			pRC->m_material.SetVec3f("_CameraPos", pCamera->m_pGameObject->GetTransform()->Position);
			pRC->m_material.SetU32("_NumLights", lights.size());
			
			for (size_t i = 0; i < lights.size(); i++)
				pRC->m_material.SetLight("_Lights[" + std::to_string(i) + "]", lights.at(i)->m_light);
			pRC->m_material.setValuesInShader();

			glBindVertexArray(pRC->m_inputLayout);
			glDrawElements(GL_TRIANGLES, pRC->m_indicesCount, GL_UNSIGNED_INT, 0);
		}
	}

	void Renderer::drawTerrainComponents(GameObject * pGO, CameraComponent * pCamera, Matrix &mViewProj, std::vector<LightComponent*> lights)const
	{
		const std::vector<TerrainComponent*> &terrainComps = pGO->GetComponentsOfType<TerrainComponent>("TerrainComponent");

		for (std::vector<TerrainComponent*>::const_iterator terrain = terrainComps.begin(); terrain != terrainComps.end(); terrain++)
		{
			RenderingComponent rc = (*terrain)->GetRC();
			glUseProgram(rc.m_material.GetShaderProgram()->m_shaderProgram);

			Matrix m = pGO->GetTransform()->CreateWorldMatrix();

			Matrix wvp = mViewProj * m;
			rc.m_material.SetMatrix4x4("_WVP", wvp);
			rc.m_material.setValuesInShader();

			glBindVertexArray(rc.m_inputLayout);
			glDrawElements(GL_TRIANGLES, rc.m_indicesCount, GL_UNSIGNED_INT, 0);

		} // Terrain Components
	}

	void Renderer::drawSkyboxComponent(CameraComponent * pCamera, Matrix &mViewProj)const
	{
		SkyboxComponent * pSC = pCamera->GetSkybox();
		if (pSC->Enabled)
		{
			glDepthFunc(GL_LEQUAL);
			glDepthMask(GL_FALSE);
			glCullFace(GL_FRONT);

			glUseProgram(pSC->GetRenderingComponent().m_material.GetShaderProgram()->m_shaderProgram);

			Matrix translation = MatrixTranslation(Vector(pCamera->m_pGameObject->GetTransform()->Position));
			Matrix wvp = mViewProj * translation;
			pSC->GetRenderingComponent().m_material.SetMatrix4x4("_WVP", wvp);
			pSC->GetRenderingComponent().m_material.setValuesInShader();
			glBindVertexArray(pSC->GetRenderingComponent().m_inputLayout);
			glDrawElements(GL_TRIANGLES, pSC->GetRenderingComponent().m_indicesCount, GL_UNSIGNED_INT, 0);
		}
	}
}