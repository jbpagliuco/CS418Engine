#pragma once

#include <vector>

#include "ShaderProgram.h"

namespace CS418
{
	class Material
	{
	public:
		~Material();

		// Initializes this material.
		// - pShaderProgram: A pointer to this material's shader.
		void Initialize(ShaderProgram * pShaderProgram);

		// Returns a pointer to this material's reference.
		ShaderProgram * GetShaderProgram()const;

	private:
		ShaderProgram* m_pShader;
	};
}