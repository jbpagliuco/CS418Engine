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

	void Scene::Initialize(LuaManager * pLuaManager)
	{
		m_pLuaManager = pLuaManager;
	}

	const std::vector<GameObject*> & Scene::GetVisibleGameObjects()const
	{
		return m_gameObjects;
	}

	void Scene::AddGameObject(GameObject *gameObject)
	{
		m_gameObjects.push_back(gameObject);
	}

	void Scene::AddCamera(CameraComponent * pCamera)
	{
		m_pCameras.push_back(pCamera);
	}

	void Scene::AddPointLight(PointLightComponent * pPointLightComponent)
	{
		m_pPointLights.push_back(pPointLightComponent);
	}

	std::vector<CameraComponent*> Scene::GetCameras()
	{
		return m_pCameras;
	}

	std::vector<PointLightComponent*> Scene::GetPointLights()
	{
		return m_pPointLights;
	}

	void Scene::Update(const GameTimer *gameTimer)
	{
		m_pLuaManager->Push("camera", *(m_pCameras.at(0)));

		for (GO_It it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
		{
			GameObject * pGO = (*it);

			std::vector<ScriptComponent*> scripts = pGO->GetComponentsOfType<ScriptComponent>("ScriptComponent");
			typedef std::vector<ScriptComponent*>::iterator Comp_It;

			for (Comp_It compIt = scripts.begin(); compIt != scripts.end(); compIt++)
			{
				ScriptComponent *pSC = (*compIt);
				
				if (pSC->Enabled)
					pSC->Update(gameTimer);
			}
		}
	}
}