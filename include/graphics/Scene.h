#pragma once

#include "GameObject.h"

namespace CS418
{
	class Scene
	{
	public:
		virtual ~Scene();

		virtual void Initialize();

		virtual const std::vector<GameObject*> & GetVisibleGameObjects()const;

		virtual void AddGameObject(GameObject *gameObject);
		
	private:
		std::vector<GameObject*> m_gameObjects;
	};
}