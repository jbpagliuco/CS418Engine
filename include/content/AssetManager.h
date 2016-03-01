#pragma once

#include <map>
#include <string>
#include <vector>

#include "util/Util.h"
#include "util/RefCount.h"

#include "graphics/Scene.h"
#include "graphics/Mesh.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture2D.h"

#include "engine/LuaManager.h"
#include "graphics/GraphicsManager.h"

namespace CS418
{
	class AssetManager
	{
	public:
		virtual ~AssetManager();

		void Initialize(LuaManager * pLuaManager, GraphicsManager * pGFXManager);

		Scene * LoadScene(const std::string &sceneFilepath);

		Mesh * LoadMesh(const std::string &meshFilepath);
		ShaderProgram * LoadShader(const std::string &vertexShaderFilepath, const std::string &fragShaderFilepath);
		Texture2D * LoadTexture2D(const std::string &texture2DFilepath);

		void UnloadContent();

	private:
		template <typename T>
		struct AssetContainer
		{
			T * Asset;
			RefCount<U32> Count;
		};

		typedef std::map<std::string, AssetContainer<Scene>> SceneContainer_t;
		typedef std::map<std::string, AssetContainer<Mesh>> MeshContainer_t;
		typedef std::map<std::string, AssetContainer<ShaderProgram>> ShaderContainer_t;
		typedef std::map<std::string, AssetContainer<Texture2D>> Texture2DContainer_t;

		SceneContainer_t m_scenes;
		MeshContainer_t m_meshes;
		ShaderContainer_t m_shaders;
		Texture2DContainer_t m_texture2Ds;

		LuaManager * m_pLuaManager;
		GraphicsManager * m_pGFXManager;
	};
}