#include "graphics/Scene.h"

#include "components/ScriptComponent.h"

namespace CS418
{
	Scene::~Scene()
	{
		for (GO_It it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
		{
			delete (*it);
		}
	}

	void Scene::Initialize()
	{

	}

	const std::vector<GameObject*> & Scene::GetVisibleGameObjects()const
	{
		return m_gameObjects;
	}

	void Scene::AddGameObject(GameObject *gameObject)
	{
		m_gameObjects.push_back(gameObject);
	}

	void Scene::Update(const GameTimer *gameTimer)
	{
		for (GO_It it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
		{
			GameObject * pGO = (*it);

			std::vector<GameComponent*> scripts = pGO->GetComponentsOfType("ScriptComponent");
			typedef std::vector<GameComponent*>::iterator Comp_It;

			for (Comp_It compIt = scripts.begin(); compIt != scripts.end(); compIt++)
			{
				ScriptComponent * pSC = (ScriptComponent*)(*compIt);
				pSC->Update(gameTimer);
			}
		}
	}
}