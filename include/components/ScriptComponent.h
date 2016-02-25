#pragma once

#include "Behaviour.h"

#include "util/GameTimer.h"
#include "engine/LuaManager.h"

namespace CS418
{
	class ScriptComponent : public Behaviour
	{
	public:
		ScriptComponent(const std::string &type = "ScriptComponent");
		virtual ~ScriptComponent();

		virtual void Initialize(LuaManager * pLuaManager, const std::string &scriptFile);

		virtual void Update(const GameTimer &gameTimer);

	private:
		LuaManager * m_pLuaManager;
		std::string m_scriptFile;
	};
}