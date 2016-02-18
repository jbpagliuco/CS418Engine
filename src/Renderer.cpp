#include "graphics/Renderer.h"

#include <GL/glew.h>

#include "graphics/RenderingComponent.h"

#include "util\ColorDefs.h"

namespace CS418
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize()
	{
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
		// Set polygon mode to fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Set line point size
		glPointSize(4.0f);

		glewInit();

		glViewport(0, 0, 800, 600);
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
					glBindVertexArray(rc->m_inputLayout);
					//glDrawArrays(GL_TRIANGLES, 0, 3);
					glDrawElements(GL_TRIANGLES, rc->m_indicesCount, GL_UNSIGNED_INT, 0);
					glBindVertexArray(0); // Is this really needed?
				}
			}
		}
	}
}