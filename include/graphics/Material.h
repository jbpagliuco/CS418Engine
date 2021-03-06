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

		void SetU32(const std::string &name, U32 value);

		void SetF32(const std::string &name, F32 value);
		void SetVec2f(const std::string &name, VECTOR2F value);
		void SetVec3f(const std::string &name, VECTOR3F value);
		void SetVec4f(const std::string &name, VECTOR4F value);

		void SetMatrix4x4(const std::string &name, const Matrix &value);

		void SetTexture2D(const std::string &name, const Texture2DGL &value);
		void SetTextureCube(const std::string &name, const TextureCube &value);

		void SetLight(const std::string &name, const Light &value);

	private:
		void setValuesInShader()const;

	private:
		ShaderProgram* m_pShader;

		std::map<std::string, U32> m_varUI;

		std::map<std::string, F32> m_varF;
		std::map<std::string, VECTOR2F> m_var2F;
		std::map<std::string, VECTOR3F> m_var3F;
		std::map<std::string, VECTOR4F> m_var4F;

		std::map<std::string, Matrix> m_varM;

		template <typename T>
		struct IndexedElement
		{
			T element;
			U32 index;
		};
		std::map<std::string, IndexedElement<Texture2DGL>> m_varT2D;
		std::map<std::string, IndexedElement<TextureCube>> m_varTC;

		std::map<std::string, Light> m_varLights;

		friend class Renderer;
	};
}