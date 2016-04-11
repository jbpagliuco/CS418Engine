#include "components/ScriptComponent.h"

#include "engine/LuaManager.h"

#include "math/Vector.h"
#include "util/Convert.h"

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

	ScriptComponent * CreateScriptComponent(std::vector<std::string> arguments, LuaManager * pLM)
	{
		ScriptComponent * pSC = new ScriptComponent;
		pSC->Initialize(pLM, arguments.at(0));
		pSC->Enabled = StringToBoolean(arguments.at(1));

		pSC->StartSetup();
		for (size_t i = 2; i < arguments.size(); i++)
		{
			std::vector<std::string> var = SplitString(arguments.at(i), ":");

			std::string key = var.at(0);
			std::string type = var.at(1);
			std::string value = var.at(2);

			if (type == "String")
				pSC->SetVariable(key, value);
			else if (type == "F32")
				pSC->SetVariable(key, StringToFloat(value));
			else if (type == "Boolean")
				pSC->SetVariable(key, StringToBoolean(value));
			else if (type == "Vector2f")
				pSC->SetVariable(key, StringToVector2f(value));
			else if (type == "Vector3f")
				pSC->SetVariable(key, StringToVector3f(value));
			else if (type == "Vector4f")
				pSC->SetVariable(key, StringToVector4f(value));
			else if (type == "Color")
				pSC->SetVariable(key, StringToColor(value));
		}

		return pSC;
	}
}