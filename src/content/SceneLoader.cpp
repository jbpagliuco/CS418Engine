#include "content/SceneLoader.h"

#include "util/FileReader.h"
#include <sstream>

#include "game/GameObject.h"

#include "components/Transform.h"
#include "components/RenderingComponent.h"
#include "components/ScriptComponent.h"

#include "util/Memory.h"

namespace CS418
{
	F32 StringToFloat(const std::string &line);
	VECTOR3F LoadVector3f(std::string line);

	std::vector<std::string> GetArguments(const std::string &line);
	GameComponent * LoadComponent(AssetManager *pAssetManager, std::string line, LuaManager * pLuaManager);

	Scene * LoadCS418Scene(AssetManager * assetManager, const std::string &sceneData, LuaManager * pLuaManager);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Scene * LoadScene(AssetManager * pAssetManager, const std::string &sceneFilepath, LuaManager * pLuaManager)
	{
		FileReader fileReader;
		Scene * pScene;

		fileReader.Open(sceneFilepath);
		if (fileReader.GetFileExtension() == ".cs418scene")
		{
			std::string sceneData = fileReader.FileAsString();
			pScene = LoadCS418Scene(pAssetManager, sceneData, pLuaManager);
		}
		else
			pScene = nullptr;

		fileReader.Close();

		return pScene;
	}


	Scene * LoadCS418Scene(AssetManager * pAssetManager, const std::string &sceneData, LuaManager * pLuaManager)
	{
		std::istringstream stream(sceneData);
		std::string line;

		Scene * pScene = new Scene;
		GameObject * pGO = nullptr;

		while (std::getline(stream, line))
		{
			if (line.empty())
				continue;

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
				{
					GameComponent * gc = LoadComponent(pAssetManager, line.substr(2), pLuaManager);
					if (line.find("- Transform") == 0)
						pGO->SetTransform((Transform*)gc);
					else
						pGO->AddComponent(gc); // No hyphen or space

					gc->SetGameObject(pGO);
				}
			}
			else if (line.at(0) == '>')
			{
				// This is for a child game object
			}
		}

		if (pGO)
			pScene->AddGameObject(pGO);

		return pScene;
	}


	std::vector<std::string> GetArguments(const std::string &line)
	{
		// No arguments
		if (line.find(' ') == std::string::npos)
			return std::vector<std::string>();


		std::string arguments = line.substr(line.find(' ') + 1);
		std::vector<std::string> v;

		size_t pos;
		while ((pos = arguments.find(",")) != std::string::npos)
		{
			std::string arg = arguments.substr(0, pos);
			v.push_back(arg);
			arguments.erase(0, pos + 1);
		}
		v.push_back(arguments);

		return v;
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
	// line == (X Y Z)
	VECTOR3F LoadVector3f(std::string line)
	{
		VECTOR3F v;

		size_t first = line.find_first_of(' ');
		size_t last = line.find_last_of(' ');
		std::string x = line.substr(1, first - 1);
		std::string y = line.substr(first + 1, last - (first + 1));
		std::string z = line.substr(last + 1, (line.length() - 1) - (last + 1));

		v.x = StringToFloat(x);
		v.y = StringToFloat(y);
		v.z = StringToFloat(z);

		return v;
	}


	GameComponent * LoadComponent(AssetManager *pAssetManager, std::string line, LuaManager * pLuaManager)
	{
		GameComponent * pGC = nullptr;

		std::string componentType = line.substr(0, line.find(' '));
		std::vector<std::string> arguments = GetArguments(line);

		if (componentType == "Transform")
		{
			std::string position = arguments.at(0);
			std::string rotation = arguments.at(1);
			std::string scale = arguments.at(2);

			pGC = (GameComponent*)AllocateAligned(sizeof(Transform), 16);
			((Transform*)pGC)->Position = LoadVector3f(position);
			((Transform*)pGC)->Rotation = LoadVector3f(rotation);
			((Transform*)pGC)->Scale = LoadVector3f(scale);
		}
		else if (componentType == "RenderingComponent")
		{
			Mesh * pMesh = pAssetManager->LoadMesh(arguments.at(0));
			ShaderProgram * pShader = pAssetManager->LoadShader(arguments.at(1), arguments.at(2));

			Material mat;
			mat.Initialize(pShader);

			pGC = new RenderingComponent;
			((RenderingComponent*)pGC)->Initialize(pMesh, mat);
		}
		else if (componentType == "ScriptComponent")
		{
			pGC = new ScriptComponent;
			((ScriptComponent*)pGC)->Initialize(pLuaManager, arguments.at(0));
		}

		return pGC;
	}
}