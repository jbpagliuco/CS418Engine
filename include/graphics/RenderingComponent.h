#pragma once

#include "GameComponent.h"

#include "Mesh.h"
#include "Material.h"

namespace CS418
{
	class RenderingComponent : public GameComponent
	{
	public:
		RenderingComponent(std::string name);
		virtual ~RenderingComponent();

		virtual void Initialize(Mesh * pMesh, Material material);
		
		virtual void Update();

	private:
		U32 m_VB;
		U32 m_IB;
		U32 m_inputLayout;

		Material m_material;
	};
}