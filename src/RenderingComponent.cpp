#include "graphics\RenderingComponent.h"

#include <GL\glew.h>

namespace CS418
{
	RenderingComponent::RenderingComponent(std::string name) : GameComponent(name)
	{

	}

	RenderingComponent::~RenderingComponent()
	{

	}

	void RenderingComponent::Initialize(Mesh * mesh, Material * material)
	{
		VertexDesc vertexDesc = material->GetShaderProgram()->GetVertexDesc();

		glGenVertexArrays(1, &m_inputLayout);
		glGenBuffers(1, &m_VB);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(m_inputLayout);

		glBindBuffer(GL_ARRAY_BUFFER, m_VB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(), vertices, GL_STATIC_DRAW);
	}

	void RenderingComponent::Update()
	{

	}
}