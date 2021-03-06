#include "components/GameComponent.h"

namespace CS418
{
	GameComponent::GameComponent(std::string type)
	{
		m_type = type;
	}

	GameComponent::~GameComponent()
	{

	}

	void GameComponent::SetGameObject(GameObject * pGO)
	{
		m_pGameObject = pGO;
	}

	GameObject * GameComponent::GetGameObject()const
	{
		return m_pGameObject;
	}

	std::string GameComponent::GetType()const
	{
		return m_type;
	}

	void GameComponent::SetType(std::string type)
	{
		m_type = type;
	}
}