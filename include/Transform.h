#pragma once

#include "GameComponent.h"

namespace CS418
{
	class Transform : public GameComponent
	{
	public:
		Transform(std::string name);
		virtual ~Transform();
	};
}