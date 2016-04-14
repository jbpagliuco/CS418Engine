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

	void Scene::SetCamera(CameraComponent * pCamera)
	{
		m_pCamera = pCamera;
	}

	void Scene::AddLight(LightComponent * pLightComponent)
	{
		m_pLights.push_back(pLightComponent);
	}

	CameraComponent* Scene::GetCamera()const
	{
		return m_pCamera;
	}

	std::vector<LightComponent*> Scene::GetLights()const
	{
		return m_pLights;
	}

	void Scene::Update(const GameTimer *gameTimer)
	{
		m_pLuaManager->Push("camera", *(m_pCamera));

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

		for (std::vector<LightComponent*>::iterator it = m_pLights.begin(); it != m_pLights.end(); it++)
		{
			// Update position of lights.
			// Should only be for point and spot lights, however we can skip a conditional statement to check since position doesn't affect parallel lights
			(*it)->GetLight().position = (*it)->GetGameObject()->GetTransform()->Position;
		}
	}
}