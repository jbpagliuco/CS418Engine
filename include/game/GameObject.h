#pragma once

#include "components/GameComponent.h"

#include <string>
#include <vector>

#include "components/Transform.h"

#include <lua.hpp>
#include <LuaBridge.h>

namespace CS418
{
	class GameObject
	{
	public:
		GameObject(std::string name);
		virtual ~GameObject();

		void AddComponent(GameComponent *component);
		void RemoveComponent(GameComponent *component);

		const std::vector<GameComponent*> & GetComponents()const;

		template <typename T>
		std::vector<T*> GetComponentsOfType(const std::string &type)const;

		void SetTransform(Transform *transform);
		Transform * GetTransform()const;

	public:
		void Lua_SetTransform(const Transform &transform);
		Transform & Lua_GetTransform()const;

		template <typename T>
		luabridge::LuaRef Lua_GetComponentsOfType(const std::string &type, lua_State * L)const;

	private:
		typedef std::vector<GameComponent*>::iterator comp_it;
		typedef std::vector<GameComponent*>::const_iterator const_comp_it;

		std::string m_name;
		std::vector<GameComponent*> m_pComponents;
		Transform *m_pTransform;
	};









	template <typename T>
	std::vector<T*> GameObject::GetComponentsOfType(const std::string &type)const
	{
		std::vector<T*> components;

		for (const_comp_it it = m_pComponents.begin(); it != m_pComponents.end(); it++)
		{
			if ((*it)->GetType() == type)
			{
				components.push_back((T*)(*it));
			}
		}

		return components;
	}

	template <typename T>
	luabridge::LuaRef GameObject::Lua_GetComponentsOfType(const std::string &type, lua_State * L)const
	{
		std::vector<T*> c = GetComponentsOfType<T>(type);

		luabridge::LuaRef t = luabridge::newTable(L);
		for (size_t i = 0; i < c.size(); i++)
			t.append(c.at(i));

		return t;
	}
}