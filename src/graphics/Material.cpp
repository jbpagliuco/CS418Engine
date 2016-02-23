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

	void Material::SetFloat(const std::string &name, F32 value)
	{
		m_varF[name] = value;
	}

	void Material::SetVec2f(const std::string &name, VECTOR2F value)
	{
		m_var2F[name] = value;
	}

	void Material::SetVec3f(const std::string &name, VECTOR3F value)
	{
		m_var3F[name] = value;
	}

	void Material::SetVec4f(const std::string &name, VECTOR4F value)
	{
		m_var4F[name] = value;
	}

	void Material::SetMatrix4x4(const std::string &name, const Matrix &value)
	{
		m_varM[name] = value;
	}

	void Material::setValuesInShader()const
	{
		for (std::map<std::string, F32>::const_iterator it = m_varF.begin(); it != m_varF.end(); ++it)
			m_pShader->SetFloat(it->first, it->second);

		for (std::map<std::string, VECTOR2F>::const_iterator it = m_var2F.begin(); it != m_var2F.end(); ++it)
			m_pShader->SetVec2f(it->first, it->second);

		for (std::map<std::string, VECTOR3F>::const_iterator it = m_var3F.begin(); it != m_var3F.end(); ++it)
			m_pShader->SetVec3f(it->first, it->second);

		for (std::map<std::string, VECTOR4F>::const_iterator it = m_var4F.begin(); it != m_var4F.end(); ++it)
			m_pShader->SetVec4f(it->first, it->second);

		for (std::map<std::string, Matrix>::const_iterator it = m_varM.begin(); it != m_varM.end(); ++it)
			m_pShader->SetMatrix4x4(it->first, it->second);
	}
}