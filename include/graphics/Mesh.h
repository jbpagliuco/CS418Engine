#pragma once

#include "math/Vector.h"

#include <vector>

#include "graphics/Vertex.h" 

namespace CS418
{
	class Mesh
	{
	public:
		virtual ~Mesh();

		virtual void Initialize(std::vector<Vertex_t> vertices, std::vector<Index_t> indices);

		const std::vector<Vertex_t> GetVertices()const;
		const std::vector<Index_t> GetIndices()const;

	private:
		std::vector<Vertex_t> m_vertices;
		std::vector<Index_t> m_indices;
	};
}