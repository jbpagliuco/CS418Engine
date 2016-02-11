#pragma once

#include <vector>

#include "ShaderProgram.h"

namespace CS418
{
	class Material
	{
	public:
		~Material();

		ShaderProgram * GetShaderProgram();

	private:
		ShaderProgram* m_pShader;
	};
}