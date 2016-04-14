#include "content/ShaderLoader.h"

#include "util/FileReader.h"

namespace CS418
{
	ShaderProgram * LoadShader(const std::string &shaderFolder)
	{
		FileReader fileReader;
		
		fileReader.Open(shaderFolder + "/vertexShader.vert");
		std::string vertexShaderData = fileReader.FileAsString();
		fileReader.Close();
		
		fileReader.Open(shaderFolder + "/fragShader.frag");
		std::string fragShaderData = fileReader.FileAsString();
		fileReader.Close();

		ShaderProgram * pShader = new ShaderProgram;
		pShader->Initialize(vertexShaderData, fragShaderData);

		return pShader;
	}
}