#include "components/SkyboxComponent.h"

#include "content/AssetManager.h"
#include "util/Convert.h"

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
		material.SetTextureCube("Skybox", texCube);

		m_rc.Initialize(pSkyboxMesh, material);
	}

	RenderingComponent & SkyboxComponent::GetRenderingComponent()
	{
		return m_rc;
	}

	SkyboxComponent * CreateSkyboxComponent(std::vector<std::string> arguments, AssetManager * pAM)
	{
		SkyboxComponent * pSC = new SkyboxComponent;

		Texture2D * pTextures[6];
		pTextures[0] = pAM->LoadTexture2D(arguments.at(0) + "/right.jpg");
		pTextures[1] = pAM->LoadTexture2D(arguments.at(0) + "/left.jpg");
		pTextures[2] = pAM->LoadTexture2D(arguments.at(0) + "/top.jpg");
		pTextures[3] = pAM->LoadTexture2D(arguments.at(0) + "/bottom.jpg");
		pTextures[4] = pAM->LoadTexture2D(arguments.at(0) + "/back.jpg");
		pTextures[5] = pAM->LoadTexture2D(arguments.at(0) + "/front.jpg");

		ShaderProgram * pSkyboxShader = pAM->LoadShader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag");
		Mesh * pSkyboxMesh = pAM->LoadMesh("assets/models/cube.cs418mesh");

		pSC->Initialize(pTextures, pSkyboxShader, pSkyboxMesh);
		pSC->Enabled = StringToBoolean(arguments.at(1));

		return pSC;
	}
}