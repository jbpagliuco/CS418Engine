#include "graphics\ShaderProgram.h"

#include <GL\glew.h>

namespace CS418
{
	ShaderProgram::~ShaderProgram()
	{
		glDeleteShader(m_shaderProgram);
	}

	void ShaderProgram::SetProgram()const
	{

	}

	ShaderProgram CompileShaderProgram(const char *vertexShaderData, const char *fragShaderData)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderData, NULL);
		glCompileShader(vertexShader);
		// Check for compile time errors
		/*GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}*/



		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragShaderData, NULL);
		glCompileShader(fragmentShader);
		// Check for compile time errors
		/*glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}*/

		

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// Check for linking errors
		/*glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}*/
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		

		ShaderProgram shader;
		shader.m_shaderProgram = shaderProgram;

		return shader;
	}
}