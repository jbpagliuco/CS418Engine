#include "game/GameObject.h"

#include <algorithm>
#include "util/Memory.h"

namespace CS418
{
	GameObject::GameObject(std::string name) : m_pTransform()
	{
		m_name = name;
	}

	GameObject::~GameObject()
	{
		for (const_comp_it it = m_pComponents.begin(); it != m_pComponents.end(); it++)
		{
			if ((*it)->GetType() == "CameraComponent")
				FreeAlignedMemory((*it));
			else
				delete (*it);
		}
		
		FreeAlignedMemory(m_pTransform);
	}

	void GameObject::AddComponent(GameComponent *component)
	{
		m_pComponents.push_back(component);
	}

	void GameObject::RemoveComponent(GameComponent *component)
	{
		std::find(m_pComponents.begin(), m_pComponents.end(), component);
	}

	const std::vector<GameComponent*> & GameObject::GetComponents()const
	{
		return m_pComponents;
	}

	void GameObject::SetTransform(Transform *transform)
	{
		m_pTransform = transform;
	}

	Transform * GameObject::GetTransform()const
	{
		return m_pTransform;
	}


	void GameObject::Lua_SetTransform(const Transform &transform)
	{
		(*m_pTransform) = Transform(transform);
	}

	Transform & GameObject::Lua_GetTransform()const
	{
		return *m_pTransform;
	}
}