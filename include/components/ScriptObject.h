#pragma once

#include "Behaviour.h"

#include "util\GameTimer.h"

namespace CS418
{
	class ScriptObject : public Behaviour
	{
	public:
		virtual ~ScriptObject() = 0;

		virtual void Update(const GameTimer &gameTimer) = 0;
	};
}