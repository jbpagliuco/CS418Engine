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

		// Returns the type of this component.
		std::string GetType()const;

	protected:
		GameObject * m_pGameObject;

		std::string m_type;	
	};
}