#include "graphics/ShaderProgram.h"

#include <GL/glew.h>
#include <stdio.h>
#include <vector>
#include <sstream>

namespace CS418
{
	ShaderProgram::~ShaderProgram()
	{
		glDeleteShader(m_shaderProgram);
	}

	bool ShaderProgram::Initialize(std::string vertexShaderSource, std::string fragShaderSource)
	{
		if (!compileShaders(vertexShaderSource, fragShaderSource))
			return false;

		createInputLayout(vertexShaderSource);
		getUniformIDs(vertexShaderSource);

		return true;
	}

	void ShaderProgram::SetFloat(const std::string &name, F32 value)
	{
		glUniform1f(m_uniforms.find(name)->second, value);
	}

	void ShaderProgram::SetVec2f(const std::string &name, VECTOR2F value)
	{
		glUniform2f(m_uniforms.find(name)->second, value.x, value.y);
	}

	void ShaderProgram::SetVec3f(const std::string &name, VECTOR3F value)
	{
		glUniform3f(m_uniforms.find(name)->second, value.x, value.y, value.z);
	}

	void ShaderProgram::SetVec4f(const std::string &name, VECTOR4F value)
	{
		glUniform4f(m_uniforms.find(name)->second, value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::SetMatrix4x4(const std::string &name, const Matrix &value)
	{
		glUniformMatrix4fv(m_uniforms.find(name)->second, 1, GL_FALSE, &(value.AsFloatArray().at(0)));
	}

	VertexDesc ShaderProgram::GetVertexDesc()const
	{
		return m_vertexDesc;
	}
	
	bool ShaderProgram::compileShaders(std::string vertexShaderSource, std::string fragShaderSource)
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
			return false;
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
			return false;
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
			return false;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_shaderProgram = shaderProgram;

		return true;
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

	void ShaderProgram::getUniformIDs(const std::string &vertexShaderSource)
	{
		std::istringstream f(vertexShaderSource);
		std::string line;

		while (std::getline(f, line))
		{
			if (line.find_first_of("uniform ") == 0)
			{
				std::istringstream ss(line);
				std::string trash, name;
				ss >> trash >> trash >> name;
				name = name.substr(0, name.length() - 1); // Remove semicolon
				U32 id = glGetUniformLocation(m_shaderProgram, name.c_str());
				m_uniforms[name] = id;
			}
		}
	}
}