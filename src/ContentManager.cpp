#include "content\ContentManager.h"

#include <assert.h>
#include <algorithm>

#include "graphics\Vertex.h"

namespace CS418
{
	ContentManager::~ContentManager()
	{

	}


	ShaderProgram * ContentManager::LoadShader(const std::string &vertexShaderFilepath, const std::string fragShaderFilepath)
	{
		for (ShaderArray_t::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		{
			if (it->first == (vertexShaderFilepath + fragShaderFilepath))
				return &(it->second);
		}

		std::string vertexShaderData, fragShaderData;

		m_fileReader.Open(vertexShaderFilepath);
		if (m_fileReader.GetFileExtension() == ".vert")
		{
			vertexShaderData = m_fileReader.FileAsString();
			if (vertexShaderData.empty())
				return nullptr;
		}
		m_fileReader.Close();


		m_fileReader.Open(fragShaderFilepath);
		if (m_fileReader.GetFileExtension() == ".frag")
		{
			fragShaderData = m_fileReader.FileAsString();
			if (fragShaderData.empty())
				return nullptr;
		}
		m_fileReader.Close();

		ShaderProgram shader = loadGLSL(vertexShaderData, fragShaderData);

		std::string key = (vertexShaderFilepath + fragShaderFilepath);
		m_shaders[key] = shader;
		
		return &(m_shaders[key]);
	}

	Mesh * ContentManager::LoadMesh(const std::string &filepath)
	{
		for (MeshArray_t::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		{
			if (it->first == filepath)
				return &(it->second);
		}

		std::string meshData;

		m_fileReader.Open(filepath);
		if (m_fileReader.GetFileExtension() == ".obj")
		{
			meshData = m_fileReader.FileAsString();
			if (meshData.empty())
				return nullptr;
			else
			{
				Mesh mesh = loadOBJ(meshData);
				m_meshes[filepath] = mesh;

				m_fileReader.Close();
				return &(m_meshes[filepath]);
			}
		}
		m_fileReader.Close();

		return nullptr;
	}

	Scene * ContentManager::LoadScene(const std::string &filepath)
	{
		for (SceneArray_t::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
		{
			if (it->first == filepath)
				return &(it->second);
		}

		m_fileReader.Open(filepath);
		if (m_fileReader.GetFileExtension() == ".scene")
		{
			std::string sceneData = m_fileReader.FileAsString();
			if (sceneData.empty())
				return nullptr;
			else
			{
				Scene scene = loadScene(sceneData);
				m_scenes[filepath] = scene;

				m_fileReader.Close();
				return &(m_scenes[filepath]);
			}
		}
		m_fileReader.Close();

		return nullptr;
	}

	void ContentManager::UnloadContent()
	{

	}

	ShaderProgram ContentManager::loadGLSL(const std::string &vertexShaderData, const std::string &fragShaderData)
	{
		ShaderProgram shader;
		shader.Initialize(vertexShaderData, fragShaderData);

		return shader;
	}

	Mesh ContentManager::loadOBJ(const std::string &meshData)
	{
		std::istringstream stream(meshData);
		std::string line;

		std::vector<Vertex_t> vertices;
		std::vector<Index_t> indices;
		while (std::getline(stream, line))
		{
			Vertex_t vCurr;
			bool readVertex = false;
			if (line.find_first_of("v ") == 0)
			{
				readVertex = true;
				std::stringstream ss(line.substr(2));
				ss >> vCurr.position.x >> vCurr.position.y >> vCurr.position.z;
			}

			if (line.find_first_of("f ") == 0)
			{
				Index_t index1, index2, index3;
				std::stringstream ss(line);
				ss >> index1 >> index2 >> index3;
				indices.push_back(index1);
				indices.push_back(index2);
				indices.push_back(index3);
			}

			if (readVertex)
				vertices.push_back(vCurr);
		}

		Mesh mesh;
		mesh.Initialize(vertices, indices);

		return mesh;
	}

	Scene ContentManager::loadScene(const std::string &sceneData)
	{
		std::istringstream stream(sceneData);
		std::string line;

		
	}
}