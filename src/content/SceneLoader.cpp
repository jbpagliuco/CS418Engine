#include "content/SceneLoader.h"

#include "util/FileReader.h"
#include <sstream>

#include "game/GameObject.h"

#include "components/Transform.h"
#include "components/RenderingComponent.h"
#include "components/ScriptComponent.h"
#include "components/CameraComponent.h"
#include "components/SkyboxComponent.h"

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
					GameComponent * gc = LoadComponent(pGO, pAssetManager, line.substr(2), pLuaManager, pGfxManager);
					if (line.find("- Transform") == 0)
					{
						pGO->SetTransform((Transform*)gc);
						gc->SetType("Transform");
					}
					else
						pGO->AddComponent(gc); // No hyphen or space

					if (gc->GetType() == "CameraComponent")
						pScene->AddCamera((CameraComponent*)gc);
					if (gc->GetType() == "SkyboxComponent")
						pScene->GetCameras().at(pScene->GetCameras().size() - 1)->SetSkybox((SkyboxComponent*)gc);
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

		if (componentType == "Transform")
		{
			void * pAlignedMem = AllocateAligned(sizeof(Transform), 16);
			pGC = new(pAlignedMem)Transform();

			pGC->SetType("Transform");
			if (arguments.size() != 0)
			{
				std::string position = arguments.at(0);
				std::string rotation = arguments.at(1);
				std::string scale = arguments.at(2);

				((Transform*)pGC)->Position = StringToVector3f(position);
				((Transform*)pGC)->Rotation = StringToVector3f(rotation);
				((Transform*)pGC)->Scale = StringToVector3f(scale);
			}

			pGC->SetGameObject(pGO);
		}
		else if (componentType == "RenderingComponent")
		{
			Mesh * pMesh = pAssetManager->LoadMesh(arguments.at(0));
			ShaderProgram * pShader = pAssetManager->LoadShader(arguments.at(1), arguments.at(2));

			Material mat;
			mat.Initialize(pShader);

			for (U32 i = 3; i < arguments.size(); i++)
			{
				std::vector<std::string> var = SplitString(arguments.at(i), ":");

				std::string key = var.at(0).substr(1);
				std::string type = var.at(1);
				std::string value = var.at(2).substr(0, var.at(2).length() - 1);

				if (type == "Texture2D")
				{
					std::vector<std::string> textureParams = SplitString(value, " ");
					Texture2D * pTexture = pAssetManager->LoadTexture2D(textureParams.at(0));
					
					TEXTURE2D_DESC texDesc;
					if (textureParams.size() > 1)
					{
						std::stringstream ss(value);
						std::string wrapS, wrapT, filterMin, filterMag, borderColor;
						std::string trash;

						ss >> trash >> wrapS >> wrapT >> filterMin >> filterMag;
						if (textureParams.size() == 6)
							ss >> borderColor;

						texDesc.WrapS = StringToTextureWrap(wrapS);
						texDesc.WrapT = StringToTextureWrap(wrapT);
						texDesc.FilterMin = StringToTextureFilter(filterMin);
						texDesc.FilterMag = StringToTextureFilter(filterMag);
						if (borderColor != "")
							texDesc.BorderColor = StringToColor(borderColor);
					}

					Texture2DGL tex2DGL;
					tex2DGL.Initialize(pTexture, texDesc);

					mat.SetTexture2D(key, tex2DGL);
				}
			}

			pGC = new RenderingComponent;
			((RenderingComponent*)pGC)->Initialize(pMesh, mat);

			pGC->SetGameObject(pGO);
		}
		else if (componentType == "ScriptComponent")
		{
			pGC = new ScriptComponent;
			((ScriptComponent*)pGC)->Initialize(pLuaManager, arguments.at(0));
			((ScriptComponent*)pGC)->Enabled = StringToBoolean(arguments.at(1));

			((ScriptComponent*)pGC)->StartSetup();
			for (size_t i = 2; i < arguments.size(); i++)
			{
				std::vector<std::string> var = SplitString(arguments.at(i), ":");
				
				std::string key = var.at(0);
				std::string type = var.at(1);
				std::string value = var.at(2);

				if (type == "String")
					((ScriptComponent*)pGC)->SetVariable(key, value);
				else if (type == "F32")
					((ScriptComponent*)pGC)->SetVariable(key, StringToFloat(value));
				else if (type == "Boolean")
					((ScriptComponent*)pGC)->SetVariable(key, StringToBoolean(value));
				else if (type == "Vector2f")
					((ScriptComponent*)pGC)->SetVariable(key, StringToVector2f(value));
				else if (type == "Vector3f")
					((ScriptComponent*)pGC)->SetVariable(key, StringToVector3f(value));
				else if (type == "Vector4f")
					((ScriptComponent*)pGC)->SetVariable(key, StringToVector4f(value));
				else if (type == "Color")
					((ScriptComponent*)pGC)->SetVariable(key, StringToColor(value));
			}

			pGC->SetGameObject(pGO);
		}
		else if (componentType == "CameraComponent")
		{
			void * pAlignedMem = AllocateAligned(sizeof(CameraComponent), 16);
			pGC = new(pAlignedMem)CameraComponent();

			pGC->SetGameObject(pGO);

			VECTOR3F position = StringToVector3f(arguments.at(0));
			VECTOR3F target = StringToVector3f(arguments.at(1));
			VECTOR3F up = StringToVector3f(arguments.at(2));
			
			F32 fov = StringToFloat(arguments.at(3));
			Viewport v = StringToViewport(arguments.at(4), pGfxManager);

			((CameraComponent*)pGC)->Initialize(Vector(position), Vector(target), Vector(up), fov, v);
			((CameraComponent*)pGC)->Enabled = StringToBoolean(arguments.at(5));
		}
		else if (componentType == "SkyboxComponent")
		{
			pGC = new SkyboxComponent;

			Texture2D * pTextures[6];
			pTextures[0] = pAssetManager->LoadTexture2D(arguments.at(0) + "_rt.tga");
			pTextures[1] = pAssetManager->LoadTexture2D(arguments.at(0) + "_lf.tga");
			pTextures[2] = pAssetManager->LoadTexture2D(arguments.at(0) + "_up.tga");
			pTextures[3] = pAssetManager->LoadTexture2D(arguments.at(0) + "_dn.tga");
			pTextures[4] = pAssetManager->LoadTexture2D(arguments.at(0) + "_ft.tga");
			pTextures[5] = pAssetManager->LoadTexture2D(arguments.at(0) + "_bk.tga");

			ShaderProgram * pSkyboxShader = pAssetManager->LoadShader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag");
			Mesh * pSkyboxMesh = pAssetManager->LoadMesh("assets/models/cube.cs418mesh");
			
			((SkyboxComponent*)pGC)->Initialize(pTextures, pSkyboxShader, pSkyboxMesh);
			((SkyboxComponent*)pGC)->Enabled = StringToBoolean(arguments.at(1));

			pGC->SetGameObject(pGO);
		}

		return pGC;
	}
}