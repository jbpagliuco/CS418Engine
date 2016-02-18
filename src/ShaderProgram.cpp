#include "graphics/ShaderProgram.h"

#include <GL\glew.h>
#include <stdio.h>
#include <vector>

namespace CS418
{
	ShaderProgram::~ShaderProgram()
	{
		glDeleteShader(m_shaderProgram);
	}

	void ShaderProgram::Initialize(std::string vertexShaderSource, std::string fragShaderSource)
	{
		compileShaders(vertexShaderSource, fragShaderSource);
		createInputLayout(vertexShaderSource);
	}

	VertexDesc ShaderProgram::GetVertexDesc()const
	{
		return m_vertexDesc;
	}

	void ShaderProgram::compileShaders(std::string vertexShaderSource, std::string fragShaderSource)
	{
		const char * temp;

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		temp = vertexShaderSource.c_str();
		glShaderSource(vertexShader, 1, &temp, NULL);
		glCompileShader(vertexShader);
		// Check for compile time errors
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			printf("Vertex Shader Compilation Failed: %s\n", infoLog);
		}



		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		temp = fragShaderSource.c_str();
		glShaderSource(fragmentShader, 1, &temp, NULL);
		glCompileShader(fragmentShader);
		// Check for compile time errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			printf("Fragment Shader Compilation Failed: %s\n", infoLog);
		}



		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		//glBindAttribLocation(shaderProgram, 0, "position");
		glLinkProgram(shaderProgram);
		// Check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("Shader Linking Failed: %s\n", infoLog);
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_shaderProgram = shaderProgram;
	}

	void ShaderProgram::createInputLayout(std::string vertexShaderSource)
	{
		size_t newline = vertexShaderSource.find_first_of('\n');
		size_t space = vertexShaderSource.find_first_of(' ');

		size_t start = space;
		size_t end;
		while ((end = vertexShaderSource.find(',', start)) != std::string::npos && end < newline)
		{
			std::string curr = vertexShaderSource.substr(start + 1, end - (start + 1));

			if (curr == "POSITION")
				m_vertexDesc.positions = true;
			else if (curr == "NORMAL")
				m_vertexDesc.normals = true;
			else if (curr == "TEXCOORD")
				m_vertexDesc.texCoords = true;
			else if (curr == "TANGENT")
				m_vertexDesc.tangents = true;
			else if (curr == "COLOR")
				m_vertexDesc.colors = true;

			start = end + 1;
		}
	}
}