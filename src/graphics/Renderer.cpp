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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// Set line point size
		glPointSize(4.0f);

		glewInit();

		Vector2<U32> dim = gfxManager->GetWindowDimensions();
		glViewport(0, 0, dim.X, dim.Y);

			/*
		// Function pointer for the wgl extention function we need to enable/disable
		// vsync
		typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		const char *extensions = (char*)glGetString(GL_EXTENSIONS);

		if (strstr(extensions, "WGL_EXT_swap_control") == 0)
		{
			return;
		}
		else
		{
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

			if (wglSwapIntervalEXT)
				wglSwapIntervalEXT(false);
		}
		*/
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

	void Renderer::Draw()const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -2.0f);

		if (m_pScene)
		{
			const std::vector<GameObject*> gameObjects = m_pScene->GetVisibleGameObjects();

			std::vector<CameraComponent*> pCameras = m_pScene->GetCameras();
			for (std::vector<CameraComponent*>::const_iterator camera = pCameras.begin(); camera != pCameras.end(); camera++)
			{
				if (!(*camera)->Enabled)
					continue;
				Viewport vp = (*camera)->GetViewport();
				glViewport(vp.TopLeftX, vp.TopLeftY, vp.Width, vp.Height);
				glClear(GL_DEPTH_BUFFER_BIT);

				for (std::vector<GameObject*>::const_iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
				{				
					const std::vector<RenderingComponent*> &renderables = (*gameObject)->GetComponentsOfType<RenderingComponent>("RenderingComponent");

					for (std::vector<RenderingComponent*>::const_iterator renderable = renderables.begin(); renderable != renderables.end(); renderable++)
					{
						RenderingComponent *pRC = (*renderable);
						glUseProgram(pRC->m_material.GetShaderProgram()->m_shaderProgram);

						Matrix m = (*gameObject)->GetTransform()->CreateWorldMatrix();

						Matrix wvp = (*camera)->buildMatrix() * m;
						pRC->m_material.SetMatrix4x4("WVP", wvp);
						pRC->m_material.setValuesInShader();

						glBindVertexArray(pRC->m_inputLayout);
						glDrawElements(GL_TRIANGLES, pRC->m_indicesCount, GL_UNSIGNED_INT, 0);

					} // Rendering Components
				} // Game Objects
			} // Cameras
		}
	}
}