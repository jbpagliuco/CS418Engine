#pragma once

#include <string>

namespace CS418
{
	class GameComponent
	{
	public:
		GameComponent(std::string name);
		virtual ~GameComponent();

		virtual void Initialize() = 0;

		virtual void Update() = 0;

	private:
		std::string m_name;
	};
}