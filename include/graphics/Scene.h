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
		virtual void AddCamera(CameraComponent * pCameraComponent);
		virtual void AddPointLight(PointLightComponent * pPointLightComponent);

		virtual void Update(const GameTimer *gameTimer);

		virtual std::vector<CameraComponent*> GetCameras();
		virtual std::vector<PointLightComponent*> GetPointLights();
		
	private:
		std::vector<GameObject*> m_gameObjects;
		std::vector<CameraComponent*> m_pCameras;
		std::vector<PointLightComponent*> m_pPointLights;

		typedef std::vector<GameObject*>::iterator GO_It;
		typedef std::vector<GameObject*>::const_iterator GO_Const_It;

		LuaManager * m_pLuaManager;
	};
}