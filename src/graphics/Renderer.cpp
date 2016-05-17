#include "graphics/Renderer.h"

#include <GL/glew.h>

#include "content/AssetManager.h"
#include "graphics/GraphicsManager.h"
#include "components/RenderingComponent.h"
#include "components/TerrainComponent.h"

#include <Windows.h>
#include <fstream>

#include "util/ColorDefs.h"
#include "graphics/BasicMeshes.h"

#define CS418_SHADOW_BUFFER_WIDTH 2048
#define CS418_SHADOW_BUFFER_HEIGHT CS418_SHADOW_BUFFER_WIDTH

namespace CS418
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(GraphicsManager * gfxManager, AssetManager * pAM)
	{
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPointSize(4.0f);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
		glDepthFunc(GL_LESS);

		glewInit();

		Vector2<U32> dim = gfxManager->GetWindowDimensions();
		glViewport(0, 0, dim.X, dim.Y);

		m_shadowShader = *(pAM->LoadShader("assets/shaders/shadow"));
		for (int i = 0; i < CS418_MAX_SHADOW_LIGHTS; i++)
			m_shadowBuffers[i].Initialize(CS418_SHADOW_BUFFER_WIDTH, CS418_SHADOW_BUFFER_HEIGHT, true);

		m_isPostProcessing = gfxManager->IsPostProcessing();
		if (m_isPostProcessing)
		{
			m_post.Initialize(dim.X, dim.Y, false);

			Mesh quad = CreateQuad();
			Material postMat;
			postMat.Initialize(pAM->LoadShader("assets/shaders/postprocessing"));

			m_postRC.Initialize(&quad, postMat);
		}
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
			CameraComponent* pCamera = m_pScene->GetCamera();
			pCamera->Resize(width, height);
		}

		if (m_isPostProcessing)
			m_post.Resize(width, height);
	}

	void Renderer::Draw()
	{
		if (m_pScene)
		{
			if (m_isPostProcessing)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, m_post.GetID());
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			const std::vector<GameObject*> gameObjects = m_pScene->GetVisibleGameObjects();
			CameraComponent* pCamera = m_pScene->GetCamera();
			const std::vector<LightComponent*> lights = m_pScene->GetLights();

			Viewport vp = pCamera->GetViewport();
			glViewport((I32)vp.TopLeftX, (I32)vp.TopLeftY, (U32)vp.Width, (U32)vp.Height);

			drawScene(gameObjects, pCamera, lights);

			if (m_isPostProcessing)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glClear(GL_COLOR_BUFFER_BIT);
				glDisable(GL_DEPTH_TEST);

				Texture2DGL cmap, dmap;
				cmap.m_id = m_post.GetColorMap();
				dmap.m_id = m_post.GetDepthMap();

				glUseProgram(m_postRC.m_material.GetShaderProgram()->m_shaderProgram);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_post.GetColorMap());
				U32 loc = glGetUniformLocation(m_postRC.m_material.GetShaderProgram()->m_shaderProgram, "_ColorMap");
				glUniform1i(loc, 0);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_post.GetDepthMap());
				loc = glGetUniformLocation(m_postRC.m_material.GetShaderProgram()->m_shaderProgram, "_DepthMap");
				glUniform1i(loc, 1);

				glBindVertexArray(m_postRC.m_inputLayout);
				glDrawElements(GL_TRIANGLES, m_postRC.m_indicesCount, GL_UNSIGNED_INT, 0);

				glEnable(GL_DEPTH_TEST);
			}
		}
	}

	void Renderer::drawScene(std::vector<GameObject*> gameObjects, CameraComponent* pCamera, std::vector<LightComponent*> lights)const
	{
		if (pCamera->Enabled)
		{
			Viewport vp = pCamera->GetViewport();
			glViewport((I32)vp.TopLeftX, (I32)vp.TopLeftY, (U32)vp.Width, (U32)vp.Height);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Matrix mViewProj = pCamera->buildMatrix();

			for (std::vector<GameObject*>::const_iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
				drawObject((*gameObject), pCamera, lights, mViewProj);
			drawSkyboxComponent(pCamera, mViewProj);
		}
	}

	void Renderer::drawObject(GameObject *pGO, CameraComponent * pCamera, std::vector<LightComponent*> lights, Matrix & mViewProj)const
	{
		drawRenderingComponents(pGO, pCamera, mViewProj, lights);
		drawTerrainComponents(pGO, pCamera, mViewProj, lights);
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
			pRC->m_material.SetLight("_Light", lights.at(0)->m_light);
			
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
			glDepthMask(GL_TRUE);
			glCullFace(GL_FRONT);

			glUseProgram(pSC->GetRenderingComponent().m_material.GetShaderProgram()->m_shaderProgram);

			Matrix translation = MatrixTranslation(Vector(pCamera->m_pGameObject->GetTransform()->Position));
			Matrix wvp = mViewProj * translation;
			pSC->GetRenderingComponent().m_material.SetMatrix4x4("_WVP", wvp);
			pSC->GetRenderingComponent().m_material.setValuesInShader();
			glBindVertexArray(pSC->GetRenderingComponent().m_inputLayout);
			glDrawElements(GL_TRIANGLES, pSC->GetRenderingComponent().m_indicesCount, GL_UNSIGNED_INT, 0);

			// Reset scene
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);
			glCullFace(GL_BACK);
		}
	}

	void Renderer::drawSceneFromLight(const std::vector<GameObject*> gameObjects, const Light &light, size_t index)
	{
		Matrix lightView, lightProj;
		Vector lightPos = Vector(light.direction).negate();
		lightPos = Vector(lightPos.getX(), lightPos.getY(), lightPos.getZ(), 1.0f);
		lightView = MatrixLookAtLH(lightPos, Vector(0.0f, 0.0f, 0.0f, 1.0f), Vector(0.0f, 1.0f, 0.0f, 0.0f));
		lightProj = MatrixOrthoLH(100.0f, 100.0f, 0.1f, 100.0f);
		glUseProgram(m_shadowShader.m_shaderProgram);
		m_shadowShader.SetMatrix4x4("_LightSpaceMatrix", lightProj * lightView);

		// Reset scene
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glCullFace(GL_BACK);

		glViewport(0.0f, 0.0f, CS418_SHADOW_BUFFER_WIDTH, CS418_SHADOW_BUFFER_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, m_shadowBuffers[index].GetID());
		glClear(GL_DEPTH_BUFFER_BIT);

		for (std::vector<GameObject*>::const_iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
		{
			GameObject * pGO = (*gameObject);
			const std::vector<RenderingComponent*> &renderables = pGO->GetComponentsOfType<RenderingComponent>("RenderingComponent");

			for (std::vector<RenderingComponent*>::const_iterator renderable = renderables.begin(); renderable != renderables.end(); renderable++)
			{
				RenderingComponent *pRC = (*renderable);

				Matrix m = pGO->GetTransform()->CreateWorldMatrix();
				m_shadowShader.SetMatrix4x4("_World", m);

				glBindVertexArray(pRC->m_inputLayout);
				glDrawElements(GL_TRIANGLES, pRC->m_indicesCount, GL_UNSIGNED_INT, 0);
			}
		}
	}
}
