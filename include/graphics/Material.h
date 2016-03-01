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

		void SetFloat(const std::string &name, F32 value);
		void SetVec2f(const std::string &name, VECTOR2F value);
		void SetVec3f(const std::string &name, VECTOR3F value);
		void SetVec4f(const std::string &name, VECTOR4F value);

		void SetMatrix4x4(const std::string &name, const Matrix &value);


	private:
		void setValuesInShader()const;

	private:
		ShaderProgram* m_pShader;

		std::map<std::string, F32> m_varF;
		std::map<std::string, VECTOR2F> m_var2F;
		std::map<std::string, VECTOR3F> m_var3F;
		std::map<std::string, VECTOR4F> m_var4F;

		std::map<std::string, Matrix> m_varM;

		friend class Renderer;
	};
}