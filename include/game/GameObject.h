#pragma once

#include "GameComponent.h"

#include <string>
#include <vector>

#include "Transform.h"

namespace CS418
{
	class GameObject
	{
	public:
		GameObject(std::string name);
		virtual ~GameObject();

		void AddComponent(GameComponent *component);
		//void RemoveComponent(const std::string &name);
		void RemoveComponent(GameComponent *component);

		const std::vector<GameComponent*> & GetComponents()const;
		std::vector<GameComponent*> GetComponentsOfType(const std::string &type)const;
		//const std::vector<GameComponent*> & GetComponentsByname(const std::string &name)const;

		void SetTransform(Transform *transform);
		Transform * GetTransform()const;

	private:
		typedef std::vector<GameComponent*>::iterator comp_it;
		typedef std::vector<GameComponent*>::const_iterator const_comp_it;

		std::string m_name;
		std::vector<GameComponent*> m_pComponents;
		Transform *m_pTransform;
	};
}