#pragma once

#include <string>

namespace CS418
{
	class GameComponent
	{
	public:
		GameComponent(std::string name);
		virtual ~GameComponent();

<<<<<<< HEAD
		virtual void Initialize() = 0;

		virtual void Update() = 0;
=======
		virtual void Initialize() = 0;
		
		virtual void Update() = 0;
>>>>>>> c2a1787fb674f0bd6a981f3d91dee01b09029b39

	private:
		std::string m_name;
	};
}