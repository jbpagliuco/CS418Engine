#include "GameObject.h"

namespace CS418
{
	GameObject::GameObject(std::string name)
	{
		m_name = name;
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::AddComponent(GameComponent &component)
	{

	}

	void GameObject::RemoveComponent(const std::string &name)
	{

	}

	void GameObject::RemoveComponent(GameComponent &component)
	{

	}
}