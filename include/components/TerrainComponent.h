#pragma once

#include "GameComponent.h"

#include "RenderingComponent.h"

namespace CS418
{
	class AssetManager;

	class TerrainComponent : public GameComponent
	{
	public:
		TerrainComponent(const std::string &type = "TerrainComponent");
		virtual ~TerrainComponent();

		virtual void Initialize(U32 size, U32 maxHeight, ShaderProgram * pColorShader);

		RenderingComponent GetRC()const;

	private:
		void diamondSquare(U32 x1, U32 y1, U32 x2, U32 y2, U32 range, U32 level);

	private:
		RenderingComponent m_rc;
		Mesh * m_pMesh;

		U32 m_size;
		F32 ** m_heights;
	};

	TerrainComponent * CreateTerrainComponent(std::vector<std::string> arguments, AssetManager * pAM);
}