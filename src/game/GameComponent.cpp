#include "game/GameComponent.h"

namespace CS418
{
	GameComponent::GameComponent(std::string type)
	{
		m_type = type;
	}

	GameComponent::~GameComponent()
	{

	}

	std::string GameComponent::GetType()const
	{
		return m_type;
	}
}