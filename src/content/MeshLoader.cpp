#include "content/MeshLoader.h"

#include "util/FileReader.h"

#include <sstream>

namespace CS418
{
	Mesh * LoadOBJ(const std::string &meshData);


	Mesh * LoadMesh(const std::string &meshFilepath)
	{
		FileReader fileReader;

		fileReader.Open(meshFilepath);
		Mesh * pMesh;

		if (fileReader.GetFileExtension() == ".obj")
		{
			std::string meshData = fileReader.FileAsString();
			pMesh = LoadOBJ(meshData);
		}
		else
			pMesh = nullptr;

		fileReader.Close();

		return pMesh;
	}


	Mesh * LoadOBJ(const std::string &meshData)
	{
		std::istringstream stream(meshData);
		std::string line;

		std::vector<Vertex_t> vertices;
		std::vector<Index_t> indices;
		while (std::getline(stream, line))
		{
			Vertex_t vCurr;
			bool readVertex = false;
			if (line.find_first_of("v") == 0)
			{
				readVertex = true;
				std::stringstream ss(line.substr(2));
				ss >> vCurr.position.x >> vCurr.position.y >> vCurr.position.z;
			}

			if (line.find_first_of("f") == 0)
			{
				Index_t index1, index2, index3;
				std::stringstream ss(line.substr(2));
				ss >> index1 >> index2 >> index3;
				indices.push_back(index1);
				indices.push_back(index2);
				indices.push_back(index3);
			}

			if (readVertex)
				vertices.push_back(vCurr);
		}

		Mesh * pMesh = new Mesh;
		pMesh->Initialize(vertices, indices);

		return pMesh;
	}
}