#include "components/ScriptComponent.h"

#include "engine/LuaManager.h"

#include "math/Vector.h"

namespace CS418
{
	ScriptComponent::ScriptComponent(const std::string &type) : Behaviour(type)
	{
		Enabled = true;
	}

	ScriptComponent::~ScriptComponent()
	{

	}

	void ScriptComponent::Initialize(LuaManager * pLuaManager, const std::string &scriptFile)
	{
		m_pLuaManager = pLuaManager;

		m_scriptFile = scriptFile;
	}

	void ScriptComponent::StartSetup()
	{
		m_pLuaManager->ExecuteFile(m_scriptFile);
	}

	void ScriptComponent::Update(const GameTimer *gameTimer)
	{
		m_pLuaManager->Push("gameObject", (*m_pGameObject));

		m_pLuaManager->ExecuteFile(m_scriptFile);

		for (size_t i = 0; i < m_variables.size(); i++)
			m_pLuaManager->PushCopy(m_variablesKeys.at(i), m_variables.at(i));

		m_pLuaManager->GetGlobal("Update")((*gameTimer));

		for (size_t i = 0; i < m_variables.size(); i++)
			m_variables.at(i) = m_pLuaManager->GetGlobal(m_variablesKeys.at(i));
	}
}