#pragma once

#include "Behaviour.h"

#include "util/GameTimer.h"
#include "engine/LuaManager.h"

#include <vector>

namespace CS418
{
	class ScriptComponent : public Behaviour
	{
	public:
		ScriptComponent(const std::string &type = "ScriptComponent");
		virtual ~ScriptComponent();

		virtual void Initialize(LuaManager * pLuaManager, const std::string &scriptFile);

		virtual void StartSetup();

		template <typename T>
		void SetVariable(std::string key, T value);

		virtual void Update(const GameTimer *gameTimer);

	private:
		LuaManager * m_pLuaManager;
		std::string m_scriptFile;

		std::vector<std::string> m_variablesKeys;
		std::vector<luabridge::LuaRef> m_variables;
	};

	template <typename T>
	void ScriptComponent::SetVariable(std::string key, T value)
	{
		luabridge::LuaRef ref = m_pLuaManager->GetGlobal(key.c_str()) = value;
		m_variables.push_back(ref);
		m_variablesKeys.push_back(key);
	}
}