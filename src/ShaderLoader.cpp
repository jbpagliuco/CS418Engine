#include "content/ShaderLoader.h"

#include "util/FileReader.h"

namespace CS418
{
	ShaderProgram * LoadShader(const std::string &vertexShaderFilepath, const std::string &fragShaderFilepath)
	{
		FileReader fileReader;
		
		fileReader.Open(vertexShaderFilepath);
		std::string vertexShaderData = fileReader.FileAsString();
		fileReader.Close();
		
		fileReader.Open(fragShaderFilepath);
		std::string fragShaderData = fileReader.FileAsString();
		fileReader.Close();

		ShaderProgram * pShader = new ShaderProgram;
		pShader->Initialize(vertexShaderData, fragShaderData);

		return pShader;
	}
}