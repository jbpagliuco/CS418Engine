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

	void ScriptComponent::Update(const GameTimer *gameTimer)
	{
		m_pLuaManager->Push("gameObject", (*m_pGameObject));

		m_pLuaManager->ExecuteFile(m_scriptFile);

		m_pLuaManager->GetGlobal("Update")((*gameTimer));
	}
}