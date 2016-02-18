#include "graphics/Material.h"

namespace CS418
{
	Material::~Material()
	{

	}

	void Material::Initialize(ShaderProgram * pShaderProgram)
	{
		m_pShader = pShaderProgram;
	}

	ShaderProgram * Material::GetShaderProgram()const
	{
		return m_pShader;
	}
}