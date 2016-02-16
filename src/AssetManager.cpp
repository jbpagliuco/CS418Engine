#include "content\AssetManager.h"

#include "content\SceneLoader.h"
#include "content\MeshLoader.h"
#include "content\ShaderLoader.h"

namespace CS418
{
	AssetManager::~AssetManager()
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
	}

	Scene * AssetManager::LoadScene(AssetManager * assetManager, const std::string &sceneFilepath)
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
		Scene * pScene = LoadScene(this, sceneFilepath);
		
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
		// Check if mesh has already been loaded.
		for (ShaderContainer_t::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		{
			if (it->first == (vertexShaderFilepath + fragShaderFilepath))
			{
				it->second.Count.AddRef();
				return it->second.Asset;
			}
		}

		// Otherwise load the mesh.
		ShaderProgram * pShader = CS418::LoadShader(vertexShaderFilepath, fragShaderFilepath);

		// Add mesh to list.
		AssetContainer<ShaderProgram> shaderContainer;
		shaderContainer.Asset = pShader;
		shaderContainer.Count.AddRef();
		m_shaders[(vertexShaderFilepath + fragShaderFilepath)] = shaderContainer;

		return pShader;
	}
}