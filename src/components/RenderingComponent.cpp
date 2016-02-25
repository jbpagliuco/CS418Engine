#include "components/RenderingComponent.h"

#include <GL/glew.h>

namespace CS418
{
	RenderingComponent::RenderingComponent(const std::string &type) : GameComponent(type)
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
		m_material = material;

		VertexDesc vertexDesc = material.GetShaderProgram()->GetVertexDesc();
		U32 vertexStride = (3 * vertexDesc.positions) + (3 * vertexDesc.normals) + (2 * vertexDesc.texCoords) + (3 * vertexDesc.tangents) + (4 * vertexDesc.colors);
		vertexStride *= sizeof(F32);

		// Generate packed vertices list
		U32 vSize = vertexStride / sizeof(F32) * pMesh->GetVertices().size();
		float * vertices = new float[vSize];
		U32 vertexIndex = 0;
		for (U32 i =  0; vertexIndex < vSize; i++)
		{
			Vertex_t curr = pMesh->GetVertices().at(i);
			if (vertexDesc.positions)
			{
				vertices[vertexIndex++] = curr.position.x;
				vertices[vertexIndex++] = curr.position.y;
				vertices[vertexIndex++] = curr.position.z;
			}
			if (vertexDesc.normals)
			{
				vertices[vertexIndex++] = curr.normal.x;
				vertices[vertexIndex++] = curr.normal.y;
				vertices[vertexIndex++] = curr.normal.z;
			}
			if (vertexDesc.texCoords)
			{
				vertices[vertexIndex++] = curr.texCoord.x;
				vertices[vertexIndex++] = curr.texCoord.y;
			}
			if (vertexDesc.tangents)
			{
				vertices[vertexIndex++] = curr.tangent.x;
				vertices[vertexIndex++] = curr.tangent.y;
				vertices[vertexIndex++] = curr.tangent.z;
			}
			if (vertexDesc.colors)
			{
				vertices[vertexIndex++] = curr.color.x;
				vertices[vertexIndex++] = curr.color.y;
				vertices[vertexIndex++] = curr.color.z;
				vertices[vertexIndex++] = curr.color.w;
			}
		}
		
		glGenVertexArrays(1, &m_inputLayout);
		glGenBuffers(1, &m_VB);
		glGenBuffers(1, &m_IB);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(m_inputLayout);

		glBindBuffer(GL_ARRAY_BUFFER, m_VB);
		glBufferData(GL_ARRAY_BUFFER, vertexStride * pMesh->GetVertices().size(), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index_t) * pMesh->GetIndices().size(), &(pMesh->GetIndices().at(0)), GL_STATIC_DRAW);
		m_indicesCount = pMesh->GetIndices().size();

		U32 count = 0;
		U32 offset = 0;
		if (vertexDesc.positions)
		{
			glEnableVertexAttribArray(count);
			glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (3 * sizeof(F32));
			count++;
		}
		if (vertexDesc.normals)
		{
			glEnableVertexAttribArray(count);
			glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (3 * sizeof(F32));
			count++;
		}
		if (vertexDesc.texCoords)
		{
			glEnableVertexAttribArray(count);
			glVertexAttribPointer(count, 2, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (2 * sizeof(F32));
			count++;
		}
		if (vertexDesc.tangents)
		{
			glEnableVertexAttribArray(count);
			glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (3 * sizeof(F32));
			count++;
		}
		if (vertexDesc.colors)
		{
			glEnableVertexAttribArray(count);
			glVertexAttribPointer(count, 4, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)offset);
			offset += (4 * sizeof(F32));
			count++;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] vertices;
	}
}