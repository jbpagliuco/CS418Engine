#pragma once

#include "game/GameObject.h"
#include "util/GameTimer.h"
#include "components/CameraComponent.h"

namespace CS418
{
	class Scene
	{
	public:
		virtual ~Scene();

		virtual void Initialize();

		virtual const std::vector<GameObject*> & GetVisibleGameObjects()const;

		virtual void AddGameObject(GameObject *gameObject);
		virtual void AddCamera(CameraComponent * pCameraComponent);

		virtual void Update(const GameTimer *gameTimer);

		virtual std::vector<CameraComponent*> GetCameras();
		
	private:
		std::vector<GameObject*> m_gameObjects;
		std::vector<CameraComponent*> m_pCameras;

		typedef std::vector<GameObject*>::iterator GO_It;
		typedef std::vector<GameObject*>::const_iterator GO_Const_It;
	};
}