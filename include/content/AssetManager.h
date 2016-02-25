#pragma once

#include <map>
#include <string>
#include <vector>

#include "util/Util.h"
#include "util/RefCount.h"

#include "graphics/Scene.h"
#include "graphics/Mesh.h"
#include "graphics/ShaderProgram.h"

#include "engine/LuaManager.h"

namespace CS418
{
	class AssetManager
	{
	public:
		virtual ~AssetManager();

		void Initialize(LuaManager * pLuaManager);

		Scene * LoadScene(const std::string &sceneFilepath);

		Mesh * LoadMesh(const std::string &meshFilepath);
		ShaderProgram * LoadShader(const std::string &vertexShaderFilepath, const std::string &fragShaderFilepath);

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

		SceneContainer_t m_scenes;
		MeshContainer_t m_meshes;
		ShaderContainer_t m_shaders;

		LuaManager * m_pLuaManager;
	};
}