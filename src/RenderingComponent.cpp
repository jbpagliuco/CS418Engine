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

	void RenderingComponent::Initialize()
	{

	}

	void RenderingComponent::Initialize(Mesh * pMesh, Material material)
	{
		VertexDesc vertexDesc = material.GetShaderProgram()->GetVertexDesc();
		U32 vertexStride = (3 * vertexDesc.positions) + (3 * vertexDesc.normals) + (2 * vertexDesc.texCoords) + (3 * vertexDesc.tangents) + (4 * vertexDesc.colors);
		vertexStride *= sizeof(F32);

		glGenVertexArrays(1, &m_inputLayout);
		glGenBuffers(1, &m_VB);
		glGenBuffers(1, &m_IB);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(m_inputLayout);

		glBindBuffer(GL_ARRAY_BUFFER, m_VB);
		glBufferData(GL_ARRAY_BUFFER, vertexStride * pMesh->GetVertices().size(), &(pMesh->GetVertices().at(0)), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index_t) * pMesh->GetIndices().size(), &(pMesh->GetIndices().at(0)), GL_STATIC_DRAW);
		
		U32 count = 0;
		U32 offset = 0;
		for (U8 i = 0; i < vertexDesc.positions; i++)
		{
			glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (3 * sizeof(F32));
			glEnableVertexAttribArray(count);
			count++;
		}
		for (U8 i = 0; i < vertexDesc.normals; i++)
		{
			glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (3 * sizeof(F32));
			glEnableVertexAttribArray(count);
			count++;
		}
		for (U8 i = 0; i < vertexDesc.texCoords; i++)
		{
			glVertexAttribPointer(count, 2, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (2 * sizeof(F32));
			glEnableVertexAttribArray(count);
			count++;
		}
		for (U8 i = 0; i < vertexDesc.tangents; i++)
		{
			glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (3 * sizeof(F32));
			glEnableVertexAttribArray(count);
			count++;
		}
		for (U8 i = 0; i < vertexDesc.colors; i++)
		{
			glVertexAttribPointer(count, 4, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (4 * sizeof(F32));
			glEnableVertexAttribArray(count);
			count++;
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void RenderingComponent::Update()
	{

	}
}