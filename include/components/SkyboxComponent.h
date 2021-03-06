#pragma once

#include "Behaviour.h"

#include "graphics/textures/TextureCube.h"
#include "RenderingComponent.h"

namespace CS418
{
	class AssetManager;

	class SkyboxComponent : public Behaviour
	{
	public:
		SkyboxComponent(const std::string &type = "SkyboxComponent");
		~SkyboxComponent();

		void Initialize(Texture2D ** pTextures, ShaderProgram * pSkyboxShader, Mesh * pSkyboxMesh);

		RenderingComponent & GetRenderingComponent();

	private:
		U32 m_id;

		RenderingComponent m_rc;
	};

	SkyboxComponent * CreateSkyboxComponent(std::vector<std::string> arguments, AssetManager * pAM);
}