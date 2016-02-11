#include "graphics\Mesh.h"

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
}