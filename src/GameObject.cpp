#include "game/GameObject.h"

#include <algorithm>

namespace CS418
{
	GameObject::GameObject(std::string name) : m_transform()
	{
		m_name = name;
	}

	GameObject::~GameObject()
	{
		for (const_comp_it it = m_components.begin(); it != m_components.end(); it++)
		{
			delete (*it);
		}
	}

	void GameObject::AddComponent(GameComponent *component)
	{
		m_components.push_back(component);
	}

	void GameObject::RemoveComponent(GameComponent *component)
	{
		std::find(m_components.begin(), m_components.end(), component);
	}

	const std::vector<GameComponent*> & GameObject::GetComponents()const
	{
		return m_components;
	}

	std::vector<GameComponent*> GameObject::GetComponentsOfType(const std::string &type)const
	{
		std::vector<GameComponent*> gameObjects;

		for (const_comp_it it = m_components.begin(); it != m_components.end(); it++)
		{
			if ((*it)->GetType() == type)
			{
				gameObjects.push_back((*it));
			}
		}

		return gameObjects;
	}
}