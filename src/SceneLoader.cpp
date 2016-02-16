#include "content\SceneLoader.h"

#include "util\FileReader.h"
#include <sstream>

#include "game\GameObject.h"

#include "game\Transform.h"
#include "graphics\RenderingComponent.h"

namespace CS418
{
	F32 StringToFloat(const std::string &line);
	VECTOR3F LoadVector3f(std::string line);
	GameComponent * LoadComponent(AssetManager *pAssetManager, std::string line);

	Scene * LoadCS418Scene(AssetManager * assetManager, const std::string &sceneData);

	Scene * LoadScene(AssetManager * pAssetManager, const std::string &sceneFilepath)
	{
		FileReader fileReader;
		Scene * pScene;

		fileReader.Open(sceneFilepath);
		if (fileReader.GetFileExtension() == ".cs418scene")
		{
			std::string sceneData = fileReader.FileAsString();
			pScene = LoadCS418Scene(pAssetManager, sceneData);
		}
		else
			pScene = nullptr;

		fileReader.Close();

		return pScene;
	}


	Scene * LoadCS418Scene(AssetManager * pAssetManager, const std::string &sceneData)
	{
		std::istringstream stream(sceneData);
		std::string line;
		
		Scene * pScene = new Scene;
		GameObject * pGO;
		size_t pos;
		
		while (std::getline(stream, line))
		{
			if (line.at(0) != '-' || line.at(0) != '>')
			{
				// Create game object and give it a name (line == name in this case).
				pGO = new GameObject(line);

			}
			else if (line.at(0) == '-')
			{
				// This is a game component for the object.
				pGO->AddComponent(LoadComponent(pAssetManager, line.substr(1))); // No hyphen	
			}
			else if (line.at(0) == '>')
			{
				// This is for a child game 
			}
		}
	}

	F32 StringToFloat(const std::string &line)
	{
		F32 value;

		if (line == "PI")
			value = PI;
		else if (line == "2PI")
			value = PI_MUL2;
		else if (line == "PIDIV2")
			value = PI_DIV2;
		else if (line == "PIDIV3")
			value = PI_DIV3;
		else if (line == "PIDIV4")
			value = PI_DIV4;
		else if (line == "PIDIV6")
			value = PI_DIV6;
		else if (line == "3PIDIV2")
			value = PI_3DIV2;
		else
			value = stof(line);

		return value;
	}

	// line == (X, Y, Z)
	VECTOR3F LoadVector3f(std::string line)
	{
		VECTOR3F v;

		std::string x = line.substr(1, line.find_first_of(','));
		std::string y = line.substr(line.find_first_of(',') + 2, line.find_last_of(','));
		std::string z = line.substr(line.find_last_of(',') + 2, line.length() - 1);

		v.x = StringToFloat(x);
		v.y = StringToFloat(y);
		v.z = StringToFloat(z);

		return v;
	}

	GameComponent * LoadComponent(AssetManager *pAssetManager, std::string line)
	{
		GameComponent * pGC;

		std::string componentType = line.substr(0, line.find(' '));
		std::string arguments = line.substr(line.find(' ') + 1);

		if (componentType == "Transform")
		{
			std::string position = arguments.substr(arguments.find_first_of("(") + 1, arguments.find_first_of(")"));
			std::string rotation = arguments.substr(arguments.find_first_of(")") + 3, arguments.find_last_of("(") - 3);
			std::string scale = arguments.substr(arguments.find_last_of("(") + 1, arguments.find_last_of(")"));

			pGC = new Transform;
			((Transform*)pGC)->Position = LoadVector3f(position);
			((Transform*)pGC)->Rotation = LoadVector3f(rotation);
			((Transform*)pGC)->Scale = LoadVector3f(scale);
		}
		else if (componentType == "RenderingComponent")
		{
			std::string meshFilepath;
			std::string vertexShaderFilepath;
			std::string fragShaderFilepath;

			std::istringstream ss(arguments);
			ss >> meshFilepath >> vertexShaderFilepath >> fragShaderFilepath;

			Mesh * pMesh = pAssetManager->LoadMesh(meshFilepath);
			ShaderProgram * pShader = pAssetManager->LoadShader(vertexShaderFilepath, fragShaderFilepath);

			Material mat;
			mat.Initialize(pShader);

			pGC = new RenderingComponent;
			((RenderingComponent*)pGC)->Initialize(pMesh, mat);
		}

		return pGC;
	}
}