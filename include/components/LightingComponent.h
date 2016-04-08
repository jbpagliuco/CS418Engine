#pragma once

#include "Behaviour.h"

#include "graphics/lighting/Lighting.h"

namespace CS418
{
	class ParallelLightComponent : public Behaviour
	{
	public:
		ParallelLightComponent(const std::string &type = "ParallelLightComponent");
		virtual ~ParallelLightComponent();

		virtual void Initialize(ParallelLight parallelLight);

	private:
		ParallelLight m_parallelLight;

		friend class Renderer;
	};

	class PointLightComponent : public Behaviour
	{
	public:
		PointLightComponent(const std::string &type = "PointLightComponent");
		virtual ~PointLightComponent();

		virtual void Initialize(PointLight pointLight);

	private:
		PointLight m_pointLight;

		friend class Renderer;
	};
}