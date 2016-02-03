#pragma once

#include <string>

namespace CS418
{
	class GameComponent
	{
	public:
		GameComponent(std::string name);
		virtual ~GameComponent();

	private:
		std::string m_name;
	};
}