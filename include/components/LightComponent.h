#pragma once

#include "Behaviour.h"

#include <vector>
#include <string>

#include "graphics/lighting/Lighting.h"

namespace CS418
{
	class LightComponent : public Behaviour
	{
	public:
		LightComponent(const std::string &type = "LightComponent");
		virtual ~LightComponent();

		virtual void Initialize(Light light);

		virtual Light GetLight()const;
		virtual void SetLight(Light light);

	private:
		Light m_light;

		friend class Renderer;
	};

	LightComponent * CreateParallelLight(std::vector<std::string> arguments);
	LightComponent * CreatePointLight(std::vector<std::string> arguments, GameObject * pGO);
}