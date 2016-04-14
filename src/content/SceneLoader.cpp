#include "content/SceneLoader.h"

#include "util/FileReader.h"
#include <sstream>

#include "game/GameObject.h"

#include "components/Transform.h"
#include "components/RenderingComponent.h"
#include "components/ScriptComponent.h"
#include "components/CameraComponent.h"
#include "components/SkyboxComponent.h"
#include "components/TerrainComponent.h"
#include "components/LightingComponent.h"

#include "graphics/Viewport.h"

#include "util/Convert.h"
#include "util/Memory.h"

#include "graphics/Texture2D.h"
#include "graphics/Texture2DGL.h"

namespace CS418
{
	GameComponent * LoadComponent(GameObject * pGO, AssetManager *pAssetManager, std::string line, LuaManager * pLuaManager, GraphicsManager * pGfxManager);
	Scene * LoadCS418Scene(AssetManager * assetManager, const std::string &sceneData, LuaManager * pLuaManager, GraphicsManager * pGfxManager);
	
	Scene * LoadScene(AssetManager * pAssetManager, const std::string &sceneFilepath, LuaManager * pLuaManager, GraphicsManager * pGfxManager)
	{
		FileReader fileReader;
		Scene * pScene;

		fileReader.Open(sceneFilepath);
		if (fileReader.GetFileExtension() == ".cs418scene")
		{
			std::string sceneData = fileReader.FileAsString();
			pScene = LoadCS418Scene(pAssetManager, sceneData, pLuaManager, pGfxManager);
		}
		else
			pScene = nullptr;

		fileReader.Close();

		return pScene;
	}

	Scene * LoadCS418Scene(AssetManager * pAssetManager, const std::string &sceneData, LuaManager * pLuaManager, GraphicsManager * pGfxManager)
	{
		std::istringstream stream(sceneData);
		std::string line;

		Scene * pScene = new Scene;
		pScene->Initialize(pLuaManager);

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
					char c = stream.peek();
					while ((c = stream.peek()) != '-' && (c != '\n') && (c != '\0'))
					{
						std::string temp;
						std::getline(stream, temp);
						line += temp;
					}

					GameComponent * gc = LoadComponent(pGO, pAssetManager, line.substr(2), pLuaManager, pGfxManager);
					if (line.find("- Transform") == 0)
					{
						pGO->SetTransform((Transform*)gc);
						gc->SetType("Transform");
					}
					else
						pGO->AddComponent(gc); // No hyphen or space

					if (gc->GetType() == "CameraComponent")
						pScene->SetCamera((CameraComponent*)gc);
					if (gc->GetType() == "SkyboxComponent")
						pScene->GetCamera()->SetSkybox((SkyboxComponent*)gc);
					if (gc->GetType() == "LightComponent")
						pScene->AddLight((LightComponent*)gc);
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

	GameComponent * LoadComponent(GameObject * pGO, AssetManager *pAssetManager, std::string line, LuaManager * pLuaManager, GraphicsManager * pGfxManager)
	{
		GameComponent * pGC = nullptr;

		std::string componentType = line.substr(0, line.find(' '));
		std::vector<std::string> arguments;
		
		if (line.find(' ') != std::string::npos)
		{
			std::string args = line.substr(line.find(' ') + 1);
			arguments = SplitString(args, ",");
		}

		for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); it++)
		{
			RemoveCapWhitespace((*it));
		}

		if (componentType == "Transform")
			pGC = CreateTransform(arguments);
		else if (componentType == "RenderingComponent")
			pGC = CreateRenderingComponent(arguments, pAssetManager);
		else if (componentType == "ScriptComponent")
			pGC = CreateScriptComponent(arguments, pLuaManager);
		else if (componentType == "CameraComponent")
			pGC = CreateCameraComponent(arguments, pGfxManager, pGO);
		else if (componentType == "SkyboxComponent")
			pGC = CreateSkyboxComponent(arguments, pAssetManager);
		else if (componentType == "TerrainComponent")
			pGC = CreateTerrainComponent(arguments, pAssetManager);
		else if (componentType == "ParallelLightComponent")
			pGC = CreateParallelLight(arguments);
		else if (componentType == "PointLightComponent")
			pGC = CreatePointLight(arguments, pGO);

		pGC->SetGameObject(pGO);
		
		return pGC;
	}
}