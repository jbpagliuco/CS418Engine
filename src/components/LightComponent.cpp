#include "components/LightingComponent.h"

namespace CS418
{
	ParallelLightComponent::ParallelLightComponent(const std::string &type) : Behaviour(type)
	{
		Enabled = true;
	}

	ParallelLightComponent::~ParallelLightComponent()
	{

	}

	void ParallelLightComponent::Initialize(ParallelLight parallelLight)
	{
		m_parallelLight = parallelLight;
	}









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