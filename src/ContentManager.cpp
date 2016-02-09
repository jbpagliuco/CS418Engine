#include "content\ContentManager.h"

#include <assert.h>
#include <algorithm>

#include <gl\glew.h>

namespace CS418
{
	ContentManager::~ContentManager()
	{

	}


	ShaderProgram ContentManager::LoadShader(const std::string &vertexShaderFilepath, const std::string fragShaderFilepath)
	{
		for (ShaderArray_t::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		{
			if (it->first.X == vertexShaderFilepath && it->first.Y == fragShaderFilepath)
				return it->second;
		}

		std::string vertexShaderData, fragShaderData;

		m_fileReader.Open(vertexShaderFilepath);
		if (m_fileReader.GetFileExtension() == ".vert")
		{
			vertexShaderData = m_fileReader.FileAsString();
			if (vertexShaderData.empty())
				return ShaderProgram();
		}
		else
			return ShaderProgram();
		m_fileReader.Close();


		m_fileReader.Open(fragShaderFilepath);
		if (m_fileReader.GetFileExtension() == ".frag")
		{
			vertexShaderData = m_fileReader.FileAsString();
			if (vertexShaderData.empty())
				return ShaderProgram();
		}
		else
			return ShaderProgram();
		m_fileReader.Close();

		ShaderProgram shader = loadGLSL(vertexShaderData.c_str(), fragShaderData.c_str());

		Vector2<std::string> key;
		key.X = vertexShaderFilepath;
		key.Y = fragShaderFilepath;
		m_shaders[key] = shader;

		return shader;
	}

	void ContentManager::UnloadContent()
	{

	}

	ShaderProgram ContentManager::loadGLSL(const char *vertexShaderData, const char *fragShaderData)
	{
		return CompileShaderProgram(vertexShaderData, fragShaderData);
	}
}