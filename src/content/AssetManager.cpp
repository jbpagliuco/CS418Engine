#include "content/AssetManager.h"

#include "content/SceneLoader.h"
#include "content/MeshLoader.h"
#include "content/ShaderLoader.h"
#include "content/TextureLoader.h"

#include <SOIL.h>

namespace CS418
{
	AssetManager::~AssetManager()
	{
		
	}

	void AssetManager::Initialize(LuaManager * pLuaManager, GraphicsManager * pGFXManager)
	{
		m_pLuaManager = pLuaManager;
		m_pGFXManager = pGFXManager;
	}

	Scene * AssetManager::LoadScene(const std::string &sceneFilepath)
	{
		// Check if scene has already been loaded.
		for (SceneContainer_t::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
		{
			if (it->first == sceneFilepath)
			{
				it->second.Count.AddRef();
				return it->second.Asset;
			}
		}

		// Otherwise load the scene.
		Scene * pScene = CS418::LoadScene(this, sceneFilepath, m_pLuaManager, m_pGFXManager);
		
		// Add scene to list.
		AssetContainer<Scene> sceneContainer;
		sceneContainer.Asset = pScene;
		sceneContainer.Count.AddRef();
		m_scenes[sceneFilepath] = sceneContainer;
		
		return pScene;
	}

	Mesh * AssetManager::LoadMesh(const std::string &meshFilepath)
	{
		// Check if mesh has already been loaded.
		for (MeshContainer_t::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		{
			if (it->first == meshFilepath)
			{
				it->second.Count.AddRef();
				return it->second.Asset;
			}
		}

		// Otherwise load the mesh.
		Mesh * pMesh = CS418::LoadMesh(meshFilepath);

		// Add mesh to list.
		AssetContainer<Mesh> meshContainer;
		meshContainer.Asset = pMesh;
		meshContainer.Count.AddRef();
		m_meshes[meshFilepath] = meshContainer;

		return pMesh;
	}

	ShaderProgram * AssetManager::LoadShader(const std::string &vertexShaderFilepath, const std::string &fragShaderFilepath)
	{
		// Check if shader has already been loaded.
		for (ShaderContainer_t::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		{
			if (it->first == (vertexShaderFilepath + fragShaderFilepath))
			{
				it->second.Count.AddRef();
				return it->second.Asset;
			}
		}

		// Otherwise load the shader.
		ShaderProgram * pShader = CS418::LoadShader(vertexShaderFilepath, fragShaderFilepath);

		// Add shader to list.
		AssetContainer<ShaderProgram> shaderContainer;
		shaderContainer.Asset = pShader;
		shaderContainer.Count.AddRef();
		m_shaders[(vertexShaderFilepath + fragShaderFilepath)] = shaderContainer;

		return pShader;
	}

	Texture2D * AssetManager::LoadTexture2D(const std::string &texture2DFilepath)
	{
		// Check if texture has already been loaded.
		for (Texture2DContainer_t::iterator it = m_texture2Ds.begin(); it != m_texture2Ds.end(); ++it)
		{
			if (it->first == texture2DFilepath)
			{
				it->second.Count.AddRef();
				return it->second.Asset;
			}
		}

		// Otherwise load the texture.
		Texture2D * pTexture2D = CS418::LoadTexture2D(texture2DFilepath);

		// Add texture to list.
		AssetContainer<Texture2D> textureContainer;
		textureContainer.Asset = pTexture2D;
		textureContainer.Count.AddRef();
		m_texture2Ds[texture2DFilepath] = textureContainer;

		return pTexture2D;
	}

	void AssetManager::UnloadContent()
	{
		for (SceneContainer_t::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
		{
			delete it->second.Asset;
			it->second.Asset = nullptr;
		}

		for (MeshContainer_t::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		{
			delete it->second.Asset;
			it->second.Asset = nullptr;
		}

		for (ShaderContainer_t::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		{
			delete it->second.Asset;
			it->second.Asset = nullptr;
		}

		for (Texture2DContainer_t::iterator it = m_texture2Ds.begin(); it != m_texture2Ds.end(); it++)
		{
			SOIL_free_image_data(it->second.Asset->GetData());
			it->second.Asset = nullptr;
		}
	}
}