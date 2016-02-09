#pragma once

#include "GameComponent.h"

#include <string>
#include <vector>

namespace CS418
{
	class GameObject
	{
	public:
		GameObject(std::string name);
		virtual ~GameObject();

		void AddComponent(GameComponent &component);
		void RemoveComponent(const std::string &name);
		void RemoveComponent(GameComponent &component);

	private:
		std::string m_name;
		std::vector<GameComponent*> m_components;
	};
}