#pragma once

#include "Util.h"

namespace CS418
{
	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram();

		void SetProgram();

	private:
		U32 m_shaderProgram;

		friend ShaderProgram CompileShaderProgram(const char *vertexShaderData, const char *fragShaderData);
	};

	ShaderProgram CompileShaderProgram(const char *vertexShaderData, const char *fragShaderData);
}