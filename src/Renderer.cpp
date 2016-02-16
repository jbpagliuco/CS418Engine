#include "graphics/Renderer.h"

#include <GL/glew.h>

#include "graphics/RenderingComponent.h"

namespace CS418
{
	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize()
	{
		// Set clear color to cornflower blue
		glClearColor(0.396f, 0.612f, .937f, 1.0f);
		// Set polygon mode to fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Set line point size
		glPointSize(4.0f);

		glewInit();
	}

	void Renderer::SetScene(Scene * pScene)
	{
		m_pScene = pScene;
	}

	void Renderer::Draw()const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		const std::vector<GameObject*> gameObjects = m_pScene->GetVisibleGameObjects();

		for (std::vector<GameObject*>::const_iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
		{
			const std::vector<GameComponent*> &renderables = (*gameObject)->GetComponentsOfType("RenderingComponent");

			for (std::vector<GameComponent*>::const_iterator renderable = renderables.begin(); renderable != renderables.end(); renderable++)
			{
				RenderingComponent *rc = (RenderingComponent*)(*renderable);
				glUseProgram(rc->m_material.GetShaderProgram()->m_shaderProgram);
				glBindVertexArray(rc->m_inputLayout);
				glDrawElements(GL_TRIANGLES, rc->m_indicesCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0); // Is this really needed?
			}
		}
	}
}