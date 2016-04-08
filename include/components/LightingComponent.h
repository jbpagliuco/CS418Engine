#pragma once

#include "Behaviour.h"

#include "graphics/lighting/Lighting.h"

namespace CS418
{
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