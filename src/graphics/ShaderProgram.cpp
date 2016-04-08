#include "graphics/ShaderProgram.h"

#include <GL/glew.h>
#include <stdio.h>
#include <vector>
#include <sstream>

#include "util/Convert.h"

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
		getUniformIDs(vertexShaderSource, fragShaderSource);

		return true;
	}

	void ShaderProgram::SetFloat(const std::string &name, F32 value)
	{
		if (m_uniforms.find(name) != m_uniforms.end())
			glUniform1f(m_uniforms.find(name)->second, value);
	}

	void ShaderProgram::SetVec2f(const std::string &name, VECTOR2F value)
	{
		if (m_uniforms.find(name) != m_uniforms.end())
			glUniform2f(m_uniforms.find(name)->second, value.x, value.y);
	}

	void ShaderProgram::SetVec3f(const std::string &name, VECTOR3F value)
	{
		if (m_uniforms.find(name) != m_uniforms.end())
			glUniform3f(m_uniforms.find(name)->second, value.x, value.y, value.z);
	}

	void ShaderProgram::SetVec4f(const std::string &name, VECTOR4F value)
	{
		if (m_uniforms.find(name) != m_uniforms.end())
			glUniform4f(m_uniforms.find(name)->second, value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::SetMatrix4x4(const std::string &name, const Matrix &value)
	{
		if (m_uniforms.find(name) != m_uniforms.end())
			glUniformMatrix4fv(m_uniforms.find(name)->second, 1, GL_FALSE, &(value.AsFloatArray().at(0)));
	}

	void ShaderProgram::SetTexture2D(const std::string &name, const Texture2DGL &tex2D, U32 index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, tex2D.GetID());
		if (m_uniforms.find(name) != m_uniforms.end())
			glUniform1i(m_uniforms.find(name)->second, index);
	}

	void ShaderProgram::SetTextureCube(const std::string &name, const TextureCube &texCube, U32 index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texCube.GetID());
		if (m_uniforms.find(name) != m_uniforms.end())
			glUniform1i(m_uniforms.find(name)->second, index);
	}

	void ShaderProgram::SetPointLight(const std::string &name, const PointLight &pointLight)
	{
		GLuint loc = glGetUniformLocation(m_shaderProgram, (name + ".ambient").c_str());
		glUniform4f(loc, pointLight.ambient.x, pointLight.ambient.y, pointLight.ambient.z, pointLight.ambient.w);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".diffuse").c_str());
		glUniform4f(loc, pointLight.diffuse.x, pointLight.diffuse.y, pointLight.diffuse.z, pointLight.diffuse.w);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".specular").c_str());
		glUniform4f(loc, pointLight.specular.x, pointLight.specular.y, pointLight.specular.z, pointLight.specular.w);

		loc = glGetUniformLocation(m_shaderProgram, (name + ".position").c_str());
		glUniform3f(loc, pointLight.position.x, pointLight.position.y, pointLight.position.z);

		loc = glGetUniformLocation(m_shaderProgram, (name + ".att").c_str());
		glUniform3f(loc, pointLight.att.x, pointLight.att.y, pointLight.att.z);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".range").c_str());
		glUniform1f(loc, pointLight.range);

		loc = glGetUniformLocation(m_shaderProgram, (name + ".intensity").c_str());
		glUniform1f(loc, pointLight.intensity);
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
		std::string firstLine = vertexShaderSource.substr(0, vertexShaderSource.find_first_of("\n"));
		std::vector<std::string> elements = SplitString(firstLine.substr(3), ",");

		for (std::vector<std::string>::iterator it = elements.begin(); it != elements.end(); it++)
		{
			if ((*it) == "POSITION")
				m_vertexDesc.positions = true;
			else if ((*it) == "NORMAL")
				m_vertexDesc.normals = true;
			else if ((*it) == "TEXCOORD")
				m_vertexDesc.texCoords = true;
			else if ((*it) == "TANGENT")
				m_vertexDesc.tangents = true;
			else if ((*it) == "COLOR")
				m_vertexDesc.colors = true;
		}
	}

	void ShaderProgram::getUniformIDs(const std::string &vertexShaderSource, const std::string &fragShaderSource)
	{
		std::istringstream ssV(vertexShaderSource);
		std::string line;

		glUseProgram(m_shaderProgram);

		while (std::getline(ssV, line))
		{
			std::istringstream ss(line);
			std::string type;
			ss >> type;

			if (type == "uniform")
			{
				ss >> type >> type; // type now holds name of variable
				type = type.substr(0, type.length() - 1);
				U32 id = glGetUniformLocation(m_shaderProgram, type.c_str());
				m_uniforms[type] = id;
			}
		}



		std::istringstream ssF(fragShaderSource);
		while (std::getline(ssF, line))
		{
			std::istringstream ss(line);
			std::string type;
			ss >> type;

			if (type == "uniform")
			{
				ss >> type >> type; // type now holds name of variable
				type = type.substr(0, type.length() - 1);
				U32 id = glGetUniformLocation(m_shaderProgram, type.c_str());
				m_uniforms[type] = id;
			}
		}
	}
}