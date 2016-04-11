#include "components/TerrainComponent.h"

#include <fstream>

#include "graphics/Mesh.h"
#include "util/ColorDefs.h"
#include "util/Convert.h"
#include "content/AssetManager.h"

namespace CS418
{
	TerrainComponent::TerrainComponent(const std::string &type) : GameComponent(type)
	{

	}

	TerrainComponent::~TerrainComponent()
	{
		delete m_pMesh;

		for (U32 i = 0; i < m_size; i++)
			delete[] m_heights[i];
		delete[] m_heights;
	}

	void TerrainComponent::Initialize(U32 size, U32 maxHeight, ShaderProgram * pColorShader)
	{
		m_heights = new F32*[size + 1];
		for (U32 i = 0; i < size + 1; i++)
			m_heights[i] = new F32[size + 1];
		m_size = size + 1;

		for (U32 i = 0; i < m_size; i++)
			for (U32 j = 0; j < m_size; j++)
				m_heights[i][j] = 0.0f;

		F32 seed = maxHeight / 2.0f;
		m_heights[0][0] = m_heights[0][size] = m_heights[size][0] = m_heights[size][size] = seed;

		diamondSquare(0, 0, m_size, m_size, maxHeight, m_size);



		U32 width = size + 1;
		U32 depth = size + 1;
		F32 dx = 1.0f;

		U32 numVertices = width * depth;
		U32 numFaces = (width - 1) * (depth - 1) * 2;


		// Create the geometry and fill the vertex buffer. 
		std::vector<Vertex_t> vertices(numVertices);

		for (U32 i = 0; i < width; ++i)
		{
			for (U32 j = 0; j < depth; ++j)
			{
				F32 y = m_heights[i][j];

				vertices[i * depth + j].position = VECTOR3F((F32)i, y, (F32)j);

				// Color the vertex based on its height.
				if (y < 0.0f)
					vertices[i * depth + j].color = Colors::BeachSand;
				else if (y < maxHeight / 5.0f)
					vertices[i * depth + j].color = Colors::LightYellowGreen;
				else if (y < maxHeight / 3.5f)
					vertices[i * depth + j].color = Colors::DarkYellowGreen;
				else if (y < maxHeight / 2.0f)
					vertices[i * depth + j].color = Colors::DarkBrown;
				else
					vertices[i * depth + j].color = Colors::White;
			}
		}

		std::vector<U32> indices(numFaces * 3);
		int k = 0;
		for (U32 i = 0; i < width - 1; ++i)
		{
			for (U32 j = 0; j < depth - 1; ++j)
			{
				indices[k] = i * depth + j;
				indices[k + 1] = i * depth + j + 1;
				indices[k + 2] = (i + 1) * depth + j;

				indices[k + 3] = (i + 1) * depth + j;
				indices[k + 4] = i * depth + j + 1;
				indices[k + 5] = (i + 1) * depth + j + 1;

				k += 6; // next quad
			}
		}

		m_pMesh = new Mesh;
		m_pMesh->Initialize(vertices, indices);

		Material material;
		material.Initialize(pColorShader);

		m_rc.Initialize(m_pMesh, material);
	}

	RenderingComponent TerrainComponent::GetRC()const
	{
		return m_rc;
	}

	void TerrainComponent::diamondSquare(U32 x1, U32 y1, U32 x2, U32 y2, U32 range, U32 level)
	{
		if (level < 1) return;

		// diamonds
		for (U32 i = x1 + level; i < x2; i += level)
		{
			for (U32 j = y1 + level; j < y2; j += level)
			{
				F32 a = m_heights[i - level][j - level];
				F32 b = m_heights[i][j - level];
				F32 c = m_heights[i - level][j];
				F32 d = m_heights[i][j];
				F32 e = m_heights[i - level / 2][j - level / 2] = (a + b + c + d) / 4 + ((rand() / (F32)RAND_MAX) * range);
			}
		}

		// squares
		for (U32 i = x1 + 2 * level; i < x2; i += level)
		{
			for (U32 j = y1 + 2 * level; j < y2; j += level)
			{
				F32 a = m_heights[i - level][j - level];
				F32 b = m_heights[i][j - level];
				F32 c = m_heights[i - level][j];
				F32 d = m_heights[i][j];
				F32 e = m_heights[i - level / 2][j - level / 2];

				F32 f = m_heights[i - level][j - level / 2] = (a + c + e + m_heights[i - 3 * level / 2][j - level / 2]) / 4 + ((rand() / (F32)RAND_MAX) * range);
				F32 g = m_heights[i - level / 2][j - level] = (a + b + e + m_heights[i - level / 2][j - 3 * level / 2]) / 4 + ((rand() / (F32)RAND_MAX) * range);
			}
		}

		diamondSquare(x1, y1, x2, y2, range / 2, level / 2);
	}

	TerrainComponent * CreateTerrainComponent(std::vector<std::string> arguments, AssetManager * pAM)
	{
		F32 size = StringToFloat(arguments.at(0));
		F32 maxHeight = StringToFloat(arguments.at(1));

		ShaderProgram * pColorShader = pAM->LoadShader("assets/shaders/color.vert", "assets/shaders/color.frag");

		TerrainComponent * pTC = new TerrainComponent;
		pTC->Initialize((U32)size, (U32)maxHeight, pColorShader);

		return pTC;
	}
}