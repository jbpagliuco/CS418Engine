#include "components/SkyboxComponent.h"

namespace CS418
{
	SkyboxComponent::SkyboxComponent(const std::string &type) : Behaviour(type)
	{
		Enabled = true;
	}
	
	SkyboxComponent::~SkyboxComponent()
	{

	}

	void SkyboxComponent::Initialize(Texture2D ** pTextures, ShaderProgram * pSkyboxShader, Mesh * pSkyboxMesh)
	{
		TextureCube texCube;
		texCube.Initialize(pTextures);

		Material material;
		material.Initialize(pSkyboxShader);
		material.SetTextureCube("_Skybox", texCube);

		m_rc.Initialize(pSkyboxMesh, material);
	}

	RenderingComponent & SkyboxComponent::GetRenderingComponent()
	{
		return m_rc;
	}
}