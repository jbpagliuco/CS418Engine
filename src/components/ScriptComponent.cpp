#include "components/ScriptComponent.h"

#include "engine/LuaManager.h"

#include "math/Vector.h"

namespace CS418
{
	ScriptComponent::ScriptComponent(const std::string &type) : Behaviour(type)
	{

	}

	ScriptComponent::~ScriptComponent()
	{

	}

	void ScriptComponent::Initialize(LuaManager * pLuaManager, const std::string &scriptFile)
	{
		m_pLuaManager = pLuaManager;

		m_scriptFile = scriptFile;
	}

	void ScriptComponent::Update(const GameTimer &gameTimer)
	{
		m_pLuaManager->Push("gameObject", (*m_pGameObject));
		m_pLuaManager->Push("gameTimer", gameTimer);

		m_pLuaManager->ExecuteFile(m_scriptFile);
		luabridge::LuaRef update = m_pLuaManager->GetGlobal("Update");
		
		try {
			update();
		}
		catch (luabridge::LuaException const& e) {
			printf("%s\n", e.what());
		}
	}
}