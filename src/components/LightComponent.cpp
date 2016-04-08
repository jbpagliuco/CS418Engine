#include "components/LightingComponent.h"

namespace CS418
{
	PointLightComponent::PointLightComponent(const std::string &type) : Behaviour(type)
	{
		Enabled = true;
	}

	PointLightComponent::~PointLightComponent()
	{

	}

	void PointLightComponent::Initialize(PointLight pointLight)
	{
		m_pointLight = pointLight;
	}
}