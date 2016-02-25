#pragma once

#include "components/GameComponent.h"

#include <string>
#include <vector>

#include "components/Transform.h"

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
		std::vector<GameComponent*> GetComponentsOfType(const std::string &type)const;

		void SetTransform(Transform *transform);
		Transform * GetTransform()const;

	public:
		void Lua_SetTransform(const Transform &transform);
		Transform & Lua_GetTransform()const;

	private:
		typedef std::vector<GameComponent*>::iterator comp_it;
		typedef std::vector<GameComponent*>::const_iterator const_comp_it;

		std::string m_name;
		std::vector<GameComponent*> m_pComponents;
		Transform *m_pTransform;

		friend class LuaManager;
	};
}