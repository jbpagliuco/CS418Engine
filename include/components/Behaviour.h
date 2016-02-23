#pragma once

#include "GameComponent.h"

namespace CS418
{
	class Behaviour : public GameComponent
	{
	public:
		virtual ~Behaviour() = 0;

	public:
		bool Enabled;
	};
}