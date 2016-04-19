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

	void ShaderProgram::SetU32(const std::string &name, U32 value)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end())
			glUniform1i(m_uniforms.find(uniName)->second + StringArrayIndex(name), value);
	}

	void ShaderProgram::SetF32(const std::string &name, F32 value)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end())
			glUniform1f(m_uniforms.find(uniName)->second + StringArrayIndex(name), value);
	}

	void ShaderProgram::SetVec2f(const std::string &name, VECTOR2F value)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end())
			glUniform2f(m_uniforms.find(uniName)->second + StringArrayIndex(name), value.x, value.y);
	}

	void ShaderProgram::SetVec3f(const std::string &name, VECTOR3F value)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end())
			glUniform3f(m_uniforms.find(uniName)->second + StringArrayIndex(name), value.x, value.y, value.z);
	}

	void ShaderProgram::SetVec4f(const std::string &name, VECTOR4F value)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end())
			glUniform4f(m_uniforms.find(uniName)->second + StringArrayIndex(name), value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::SetMatrix4x4(const std::string &name, const Matrix &value)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end())
			glUniformMatrix4fv(m_uniforms.find(uniName)->second + StringArrayIndex(name), 1, GL_FALSE, &(value.AsFloatArray().at(0)));
	}

	void ShaderProgram::SetTexture2D(const std::string &name, const Texture2DGL &tex2D, U32 index)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end() && m_uniforms.find(uniName)->second != -1)
		{
			U32 arrayIndex = StringArrayIndex(name);
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_2D, tex2D.GetID());
			U32 s = glGetUniformLocation(m_shaderProgram, name.c_str());
			glUniform1i(s, index);
		}
	}

	void ShaderProgram::SetTextureCube(const std::string &name, const TextureCube &texCube, U32 index)
	{
		std::string uniName = StringWithoutArray(name);
		if (m_uniforms.find(uniName) != m_uniforms.end())
		{
			U32 arrayIndex = StringArrayIndex(name);
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texCube.GetID());
			glUniform1i(m_uniforms.find(uniName)->second + arrayIndex, index);
		}
	}

	void ShaderProgram::SetLight(const std::string &name, const Light &light)
	{
		GLuint loc = glGetUniformLocation(m_shaderProgram, (name + ".ambient").c_str());
		glUniform4f(loc, light.ambient.x, light.ambient.y, light.ambient.z, light.ambient.w);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".diffuse").c_str());
		glUniform4f(loc, light.diffuse.x, light.diffuse.y, light.diffuse.z, light.diffuse.w);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".specular").c_str());
		glUniform4f(loc, light.specular.x, light.specular.y, light.specular.z, light.specular.w);

		loc = glGetUniformLocation(m_shaderProgram, (name + ".position").c_str());
		glUniform3f(loc, light.position.x, light.position.y, light.position.z);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".direction").c_str());
		glUniform3f(loc, light.direction.x, light.direction.y, light.direction.z);

		loc = glGetUniformLocation(m_shaderProgram, (name + ".att").c_str());
		glUniform3f(loc, light.att.x, light.att.y, light.att.z);

		loc = glGetUniformLocation(m_shaderProgram, (name + ".range").c_str());
		glUniform1f(loc, light.range);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".intensity").c_str());
		glUniform1f(loc, light.intensity);

		loc = glGetUniformLocation(m_shaderProgram, (name + ".type").c_str());
		glUniform1i(loc, light.type);
		loc = glGetUniformLocation(m_shaderProgram, (name + ".castsShadows").c_str());
		glUniform1i(loc, light.castsShadows);
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
				type = SplitString(type, "[").at(0);
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
				type = SplitString(type, "[").at(0);
				U32 id = glGetUniformLocation(m_shaderProgram, type.c_str());
				m_uniforms[type] = id;
			}
		}
	}
}