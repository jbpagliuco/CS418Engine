#pragma once

#include <string>

namespace CS418
{
	class GameComponent
	{
	public:
		GameComponent(std::string name);
		virtual ~GameComponent();

		virtual void Initialize();

		virtual void Update();

	private:
		std::string m_name;
	};
}