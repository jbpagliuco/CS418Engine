#include "graphics/Renderer.h"

#include <GL/glew.h>

#include "graphics/GraphicsManager.h"
#include "components/RenderingComponent.h"

#include "util\ColorDefs.h"
#include <Windows.h>

namespace CS418
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(GraphicsManager * gfxManager)
	{
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
		// Set polygon mode to fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Set line point size
		glPointSize(4.0f);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_pScene)
		{
			const std::vector<GameObject*> gameObjects = m_pScene->GetVisibleGameObjects();

			std::vector<CameraComponent*> pCameras = m_pScene->GetCameras();
			for (std::vector<CameraComponent*>::const_iterator camera = pCameras.begin(); camera != pCameras.end(); camera++)
			{
				if (!(*camera)->Enabled)
					continue;
				Viewport vp = (*camera)->GetViewport();
				glViewport((I32)vp.TopLeftX, (I32)vp.TopLeftY, (U32)vp.Width, (U32)vp.Height);

				glDepthFunc(GL_LESS);
				glCullFace(GL_BACK);

				glClear(GL_DEPTH_BUFFER_BIT);

				Matrix mViewProj = (*camera)->buildMatrix();

				for (std::vector<GameObject*>::const_iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
				{				
					const std::vector<RenderingComponent*> &renderables = (*gameObject)->GetComponentsOfType<RenderingComponent>("RenderingComponent");

					for (std::vector<RenderingComponent*>::const_iterator renderable = renderables.begin(); renderable != renderables.end(); renderable++)
					{
						RenderingComponent *pRC = (*renderable);
						glUseProgram(pRC->m_material.GetShaderProgram()->m_shaderProgram);

						Matrix m = (*gameObject)->GetTransform()->CreateWorldMatrix();

						Matrix wvp = mViewProj * m;
						pRC->m_material.SetMatrix4x4("WVP", wvp);
						pRC->m_material.setValuesInShader();

						glBindVertexArray(pRC->m_inputLayout);
						glDrawElements(GL_TRIANGLES, pRC->m_indicesCount, GL_UNSIGNED_INT, 0);

					} // Rendering Components
				} // Game Objects

				// Draw Skybox
				/*SkyboxComponent * pSC = (*camera)->GetSkybox();
				if (pSC->Enabled)
				{
					glDepthFunc(GL_LEQUAL);
					glCullFace(GL_FRONT);

					glUseProgram(pSC->GetRenderingComponent().m_material.GetShaderProgram()->m_shaderProgram);
					
					Matrix wvp = (*camera)->m_pGameObject->GetTransform()->CreateWorldMatrix();
					wvp = (*camera)->buildMatrix() * wvp;
					pSC->GetRenderingComponent().m_material.SetMatrix4x4("WVP", wvp);
					pSC->GetRenderingComponent().m_material.setValuesInShader();
					glBindVertexArray(pSC->GetRenderingComponent().m_inputLayout);
					glDrawElements(GL_TRIANGLES, pSC->GetRenderingComponent().m_indicesCount, GL_UNSIGNED_INT, 0);
				}*/
			} // Cameras
		}
	}
}