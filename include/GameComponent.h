#pragma once

#include <string>

namespace CS418
{
	class GameComponent
	{
	public:
		GameComponent(std::string type);
		virtual ~GameComponent();

		// Initializes this game component.
		virtual void Initialize() = 0;

		// Returns the type of this component.
		std::string GetType()const;

	protected:
		std::string m_type;
	};
}