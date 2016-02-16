#pragma once

/*
* ALLOWED FILE EXTENSIONS:
* Shaders:
*	- .vert (GLSL vertex shader)
*	- .frag (GLSL fragment shader)
*
* Meshes:
*	- .obj (Wavefront OBJ)
*/

#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "FileReader.h"

#include "graphics\ShaderProgram.h"
#include "graphics\Mesh.h"
#include "Scene.h"

namespace CS418
{
	class ContentManager
	{
	public:
		virtual ~ContentManager();
		
		// Processes and loads an shader program.
		// - vertexShaderFilepath: The file path to the vertex shader.
		// - fragShaderFilepath:   The file path to the fragment shader.
		virtual ShaderProgram * LoadShader(const std::string &vertexShaderFilepath, const std::string fragShaderFilepath);

		// Processes and loads a mesh.
		// - filename: The file path of the mesh.
		virtual Mesh * LoadMesh(const std::string &filepath);

		// Processes and loads a scene.
		// - filename: The file path of the scene.
		virtual Scene * LoadScene(const std::string &filepath);
		
		// Disposes all data that has been loaded by this content manager.
		virtual void UnloadContent();

	protected:
		ShaderProgram loadGLSL(const std::string &vertexShaderData, const std::string &fragShaderData);
		
		Mesh loadOBJ(const std::string &meshData);

		Scene loadScene(const std::string &sceneData);

	private:
		FileReader m_fileReader;

		typedef std::map<std::string, ShaderProgram> ShaderArray_t;
		typedef std::map<std::string, Mesh> MeshArray_t;
		typedef std::map<std::string, Scene> SceneArray_t;

		ShaderArray_t m_shaders;
		MeshArray_t m_meshes;
		SceneArray_t m_scenes;
	};
}