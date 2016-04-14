#pragma once

#include "game/GameObject.h"
#include "util/GameTimer.h"
#include "components/CameraComponent.h"
#include "components/LightingComponent.h"

#include "engine/LuaManager.h"

namespace CS418
{
	class Scene
	{
	public:
		virtual ~Scene();

		virtual void Initialize(LuaManager * pLuaManager);

		virtual const std::vector<GameObject*> & GetVisibleGameObjects()const;

		virtual void AddGameObject(GameObject *gameObject);
		virtual void SetCamera(CameraComponent * pCameraComponent);
		virtual void AddLight(LightComponent * pLight);

		virtual void Update(const GameTimer *gameTimer);

		virtual CameraComponent* GetCamera()const;
		virtual std::vector<LightComponent*> GetLights()const;
		
	private:
		std::vector<GameObject*> m_gameObjects;
		CameraComponent* m_pCamera;
		std::vector<LightComponent*> m_pLights;

		typedef std::vector<GameObject*>::iterator GO_It;
		typedef std::vector<GameObject*>::const_iterator GO_Const_It;

		LuaManager * m_pLuaManager;
	};
}