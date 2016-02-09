#pragma once

#include <vector>

#include "Mesh.h"
#include "ShaderProgram.h"

namespace CS418
{
	class Model
	{
	public:
		virtual ~Model();

		virtual void Draw();

	private:
		std::vector<Mesh> m_meshes;
		ShaderProgram m_shader;
	};
}