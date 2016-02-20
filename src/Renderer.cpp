#include "graphics/Renderer.h"

#include <GL/glew.h>

#include "graphics/RenderingComponent.h"

#include "util\ColorDefs.h"
#include <Windows.h>

namespace CS418
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize()
	{
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
		// Set polygon mode to fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// Set line point size
		glPointSize(4.0f);

		glewInit();

		glViewport(0, 0, 800, 600);

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

			for (std::vector<GameObject*>::const_iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
			{
				const std::vector<GameComponent*> &renderables = (*gameObject)->GetComponentsOfType("RenderingComponent");

				for (std::vector<GameComponent*>::const_iterator renderable = renderables.begin(); renderable != renderables.end(); renderable++)
				{
					RenderingComponent *rc = (RenderingComponent*)(*renderable);
					glUseProgram(rc->m_material.GetShaderProgram()->m_shaderProgram);

					Matrix m = (*gameObject)->GetTransform()->CreateWorldMatrix();
					Vector cameraPos(0.0f, 0.5f, -10.0f, 1.0f);
					Vector lookAt(0.0f, 0.0f, 0.0f, 1.0f);
					Vector up(0.0f, 1.0f, 0.0f, 0.0f);
					Matrix v = MatrixLookAtLH(cameraPos, lookAt, up);
					Matrix p = MatrixPerspectiveFOVLH(PI_DIV4, 800.0f / 600.0f, 0.1f, 1000.0f);

					Matrix wvp = p * v * m;
					rc->m_material.SetMatrix4x4("WVP", wvp);
					rc->m_material.setValuesInShader();

					glBindVertexArray(rc->m_inputLayout);
					glDrawElements(GL_TRIANGLES, rc->m_indicesCount, GL_UNSIGNED_INT, 0);
				}
			}
		}
	}
}