#include "graphics/BasicMeshes.h"

namespace CS418
{
	Mesh CreateQuad()
	{
		Mesh m;
		std::vector<Vertex_t> vertices(4);
		std::vector<Index_t> indices;

		vertices.at(0).position = VECTOR3F(-1.0f, 1.0f, 0.0f);
		vertices.at(0).texCoord = VECTOR2F(0.0f, 1.0f);
		vertices.at(0).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		vertices.at(1).position = VECTOR3F(-1.0f, -1.0f, 0.0f);
		vertices.at(1).texCoord = VECTOR2F(0.0f, 0.0f);
		vertices.at(1).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		vertices.at(2).position = VECTOR3F(1.0f, -1.0f, 0.0f);
		vertices.at(2).texCoord = VECTOR2F(1.0f, 0.0f);
		vertices.at(2).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		vertices.at(3).position = VECTOR3F(1.0f, 1.0f, 0.0f);
		vertices.at(3).texCoord = VECTOR2F(1.0f, 1.0f);
		vertices.at(3).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		indices = { 0, 1, 2, 0, 2, 3 };

		m.Initialize(vertices, indices);

		return m;
	}
}