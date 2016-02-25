#pragma once

#include "game/GameObject.h"
#include "util/GameTimer.h"

namespace CS418
{
	class Scene
	{
	public:
		virtual ~Scene();

		virtual void Initialize();

		virtual const std::vector<GameObject*> & GetVisibleGameObjects()const;

		virtual void AddGameObject(GameObject *gameObject);

		virtual void Update(const GameTimer *gameTimer);
		
	private:
		std::vector<GameObject*> m_gameObjects;

		typedef std::vector<GameObject*>::iterator GO_It;
		typedef std::vector<GameObject*>::const_iterator GO_Const_It;
	};
}