#pragma once

#include <string>

#include "util/Util.h"

namespace CS418
{
	typedef struct VertexDesc
	{
		VertexDesc()
		{
			positions = normals = texCoords = tangents = colors = false;
		}
		bool positions;
		bool normals;
		bool texCoords;
		bool tangents;
		bool colors;
	}VertexDesc;

	class ShaderProgram
	{
	public:
		~ShaderProgram();

		void Initialize(std::string vertexShaderSource, std::string fragShaderSource);

		VertexDesc GetVertexDesc()const;

	private:
		void compileShaders(std::string vertexShaderSource, std::string fragShaderSource);
		void createInputLayout(std::string vertexShaderSource);

	private:
		U32 m_shaderProgram;
		VertexDesc m_vertexDesc;

		friend class Renderer;
	};
}