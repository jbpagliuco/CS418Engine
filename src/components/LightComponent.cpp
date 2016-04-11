#include "components/LightingComponent.h"

#include "util/Convert.h"

namespace CS418
{
	LightComponent::LightComponent(const std::string &type) : Behaviour(type)
	{
		Enabled = true;
	}

	LightComponent::~LightComponent()
	{

	}

	void LightComponent::Initialize(Light light)
	{
		m_light = light;
	}

	Light & LightComponent::GetLight()
	{
		return m_light;
	}

	LightComponent * CreateParallelLight(std::vector<std::string> arguments)
	{
		Light light;
		light.direction = StringToVector3f(arguments.at(0));
		light.ambient = StringToColor(arguments.at(1));
		light.diffuse = StringToColor(arguments.at(2));
		light.specular = StringToColor(arguments.at(3));
		light.intensity = StringToFloat(arguments.at(4));
		light.type = LIGHT_TYPE_PARALLEL;

		LightComponent * pLC = new LightComponent;

		pLC->Initialize(light);

		return pLC;
	}

	LightComponent * CreatePointLight(std::vector<std::string> arguments, GameObject * pGO)
	{
		Light light;
		light.position = pGO->GetTransform()->Position;
		light.ambient = StringToColor(arguments.at(0));
		light.diffuse = StringToColor(arguments.at(1));
		light.specular = StringToColor(arguments.at(2));
		light.att = StringToVector3f(arguments.at(3));
		light.range = StringToFloat(arguments.at(4));
		light.intensity = StringToFloat(arguments.at(5));
		light.type = LIGHT_TYPE_POINT;

		LightComponent * pLC = new LightComponent;

		pLC->Initialize(light);

		return pLC;
	}
}