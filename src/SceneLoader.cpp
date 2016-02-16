#include "content/SceneLoader.h"

#include "util/FileReader.h"
#include <sstream>

#include "game/GameObject.h"

#include "game/Transform.h"
#include "graphics/RenderingComponent.h"

namespace CS418
{
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
		GameObject * pGO = nullptr;
		
		while (std::getline(stream, line))
		{
			if (line.at(0) != '-' && line.at(0) != '>')
			{
				// If this is a new game object, add the old one to the scene.
				if (pGO)
					pScene->AddGameObject(pGO);

				// Create game object and give it a name (line == name in this case).
				pGO = new GameObject(line);

			}
			else if (line.at(0) == '-')
			{
				// This is a game component for the object.
				if (pGO)
					pGO->AddComponent(LoadComponent(pAssetManager, line.substr(2))); // No hyphen or space
			}
			else if (line.at(0) == '>')
			{
				// This is for a child game 
			}
		}

		return pScene;
	}

	VECTOR3F LoadVector3f(std::string line)
	{
		VECTOR3F v;

		size_t pos;
		std::string token;
		size_t i = 0;
		while ((pos = line.find(',')) != std::string::npos) 
		{
			token = line.substr(0, pos);

			F32 value;
			if (token.find("PI") != std::string::npos)
			{
				if (token == "PI")
					value = PI;
				else if (token == "2PI")
					value = PI_MUL2;
				else if (token == "PIDIV2")
					value = PI_DIV2;
				else if (token == "PIDIV3")
					value = PI_DIV3;
				else if (token == "PIDIV4")
					value = PI_DIV4;
				else if (token == "PIDIV6")
					value = PI_DIV6;
				else if (token == "3PIDIV2")
					value = PI_3DIV2;
			}
			else
			{
				// Just a number
				value = std::stof(token);
			}

			if (i == 0)
				v.x = value;
			else if (i == 1)
				v.y = value;
			i++;

			line.erase(0, pos + 1); // 1 for ','
		}

		return v;
	}

	GameComponent * LoadComponent(AssetManager *pAssetManager, std::string line)
	{
		GameComponent * pGC = nullptr;

		std::string componentType = line.substr(0, line.find(' '));
		std::string arguments = line.substr(line.find(' ') + 1);

		if (componentType == "Transform")
		{
			std::string position = arguments.substr(arguments.find_first_of("(") + 1, arguments.find_first_of(")") - 1);
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