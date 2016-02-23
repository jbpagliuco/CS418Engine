#pragma once

#include "GameComponent.h"

#include "graphics/Mesh.h"
#include "graphics/Material.h"

namespace CS418
{
	class RenderingComponent : public GameComponent
	{
	public:
		RenderingComponent();
		virtual ~RenderingComponent();

		virtual void Initialize();
		virtual void Initialize(Mesh * pMesh, Material material);

	private:
		U32 m_VB;
		U32 m_IB;
		U32 m_inputLayout;
		U32 m_indicesCount;

		Material m_material;

		friend class Renderer;
	};
}