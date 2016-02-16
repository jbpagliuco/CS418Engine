#include "graphics/Mesh.h"

namespace CS418
{
	Mesh::~Mesh()
	{

	}

	void Mesh::Initialize(std::vector<Vertex_t> vertices, std::vector<Index_t> indices)
	{
		m_vertices = vertices;
		m_indices = indices;
	}

	const std::vector<Vertex_t> Mesh::GetVertices()const
	{
		return m_vertices;
	}

	const std::vector<Index_t> Mesh::GetIndices()const
	{
		return m_indices;
	}
}