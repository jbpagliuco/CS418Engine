#pragma once

#include <string>

namespace CS418
{
	class GameComponent
	{
	public:
		GameComponent(std::string name);
		virtual ~GameComponent();

		// Initializes this game component.
		virtual void Initialize() = 0;

		// Returns the type of this component.
		virtual std::string GetType() = 0;

	protected:
		std::string m_name;
	};
}