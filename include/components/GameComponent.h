#pragma once

#include <string>

namespace CS418
{
	class GameObject;

	class GameComponent
	{
	public:
		GameComponent(std::string type);
		virtual ~GameComponent();

		void SetGameObject(GameObject * pGO);
		GameObject * GetGameObject()const;

		// Returns the type of this component.
		std::string GetType()const;
		void SetType(std::string type);

	protected:
		GameObject * m_pGameObject;

		std::string m_type;	
	};
}