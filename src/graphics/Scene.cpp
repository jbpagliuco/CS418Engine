#include "graphics/Scene.h"

namespace CS418
{
	Scene::~Scene()
	{

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
}