#include "content/MeshLoader.h"

#include "util/FileReader.h"

#include <sstream>
#include <algorithm>

namespace CS418
{
	struct IndexElem
	{
		IndexElem() { pos = norm = texCoord = 0; }
		U32 pos, norm, texCoord;

		bool operator==(const IndexElem &other)const
		{
			return ((pos == other.pos) && (norm == other.norm) && (texCoord == other.texCoord));
		}
	};

	Mesh * createMesh(const std::vector<VECTOR3F> &positions, const std::vector<VECTOR3F> &normals, const std::vector<VECTOR2F> &texCoords, const std::vector<IndexElem> &indices);

	Mesh * LoadOBJ(const std::string &meshData);
	Mesh * LoadCS418Mesh(const std::string &meshData);



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
		else if (fileReader.GetFileExtension() == ".cs418mesh")
		{
			std::string meshData = fileReader.FileAsString();
			pMesh = LoadCS418Mesh(meshData);
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
		
		std::vector<IndexElem> indices;
		std::vector<VECTOR3F> positions;
		std::vector<VECTOR3F> normals;
		std::vector<VECTOR2F> texCoords;

		while (std::getline(stream, line))
		{
			if (line.find_first_of("v") == 0)
			{
				std::string read = line.substr(2);
				std::istringstream ss(read);
				if (line.at(1) == ' ') // Position
				{
					VECTOR3F pos;
					ss >> pos.x >> pos.y >> pos.z;
					positions.push_back(pos);
				}
				else if (line.at(1) == 'n') // normals
				{
					VECTOR3F norm;
					ss >> norm.x >> norm.y >> norm.z;
					normals.push_back(norm);
				}
				else if (line.at(1) == 't') // tex coords
				{
					VECTOR2F tex;
					ss >> tex.x >> tex.y;
					texCoords.push_back(tex);
				}
			}

			if (line.find_first_of("f") == 0)
			{
				line = line.substr(2);
				IndexElem index[3];

				size_t numberOfSlashes = std::count(line.begin(), line.end(), '/');
				if (numberOfSlashes == 0) // Only position
				{
					std::istringstream ss(line);
					ss >> index[0].pos >> index[1].pos >> index[2].pos;
				}
				else if (numberOfSlashes == 3) // Position and texture coordinate
				{
					std::replace(line.begin(), line.end(), '/', ' ');
					std::istringstream ss(line);
					ss >> index[0].pos >> index[0].texCoord >> index[1].pos >> index[1].texCoord >> index[2].pos >> index[2].texCoord;
				}
				else if (numberOfSlashes == 6) // Either all 3 or no texCoords
				{
					if (line.find("//") != std::string::npos) // No texture coordinates
					{
						std::replace(line.begin(), line.end(), '/', ' ');
						std::istringstream ss(line);
						ss >> index[0].pos >> index[0].norm >> index[1].pos >> index[1].norm >> index[2].pos >> index[2].norm;
					}
					else // All 3
					{
						std::replace(line.begin(), line.end(), '/', ' ');
						std::istringstream ss(line);
						ss >> index[0].pos >> index[0].texCoord >> index[0].norm >> index[1].pos >> index[1].texCoord >> index[1].norm >> index[2].pos >> index[2].texCoord >> index[2].norm;
					}
				}

				indices.push_back(index[0]);
				indices.push_back(index[1]);
				indices.push_back(index[2]);
			}
		}

		return createMesh(positions, normals, texCoords, indices);
	}

	Mesh * createMesh(const std::vector<VECTOR3F> &positions, const std::vector<VECTOR3F> &normals, const std::vector<VECTOR2F> &texCoords, const std::vector<IndexElem> &indices)
	{
		std::vector<Vertex_t> finalVertices;
		std::vector<Index_t> finalIndices;
		std::vector<IndexElem> comparisonIndices;

		U32 uniqueIndices = 0;
		for (std::vector<IndexElem>::const_iterator it = indices.begin(); it != indices.end(); it++)
		{
			IndexElem curr = (*it);
			Vertex_t v;

			bool alreadyExists = false;
			for (U32 i = 0; i < comparisonIndices.size(); i++)
			{
				if (comparisonIndices.at(i) == curr)
				{
					finalIndices.push_back(i);
					alreadyExists = true;
					break;
				}
			}
			if (alreadyExists)
				continue;

			// Subtract one because elements come 1-based, not 0-based.
			if (curr.pos != 0)
				v.position = positions.at(curr.pos - 1);
			if (curr.norm != 0)
				v.normal = normals.at(curr.norm - 1);
			if (curr.texCoord != 0)
				v.texCoord = texCoords.at(curr.texCoord - 1);

			finalVertices.push_back(v);
			finalIndices.push_back(uniqueIndices++);
			comparisonIndices.push_back(curr);
		}

		Mesh * pMesh = new Mesh;
		pMesh->Initialize(finalVertices, finalIndices);

		return pMesh;
	}

	Mesh * LoadCS418Mesh(const std::string &meshData)
	{
		std::istringstream stream(meshData);
		std::string line;

		std::vector<Index_t> indices;
		std::vector<Vertex_t> vertices;

		bool readingVertices = false;
		bool readingIndices = false;

		U32 count = 0;
		while (std::getline(stream, line))
		{
			if (line == "Vertices:")
			{
				readingVertices = true;
				continue;
			}
			if (line == "Indices:")
			{
				readingIndices = true;
				continue;
			}
			if (line == "")
			{
				readingVertices = readingIndices = false;
			}

			if (readingVertices)
			{
				Vertex_t curr;

				std::istringstream ss(line);

				ss >> curr.position.x >> curr.position.y >> curr.position.z >> curr.texCoord.x >> curr.texCoord.y >> curr.normal.x >> curr.normal.y >> curr.normal.z >> curr.tangent.x >> curr.tangent.y >> curr.tangent.z >> curr.color.x >> curr.color.y >> curr.color.z >> curr.color.w;
				
				vertices.push_back(curr);
			}
			else if (readingIndices)
			{
				std::istringstream ss(line);

				Index_t i[3];
				ss >> i[0] >> i[1] >> i[2];

				indices.push_back(i[0]);
				indices.push_back(i[1]);
				indices.push_back(i[2]);
			}
		}

		Mesh * pMesh = new Mesh;
		pMesh->Initialize(vertices, indices);
		
		return pMesh;
	}
}