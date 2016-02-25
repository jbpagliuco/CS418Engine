#include "engine/LuaManager.h"

#include <LuaBridge.h>
using namespace luabridge;

#include "game/GameObject.h"
#include "components/GameComponent.h"
#include "components/Transform.h"

#include "components/Behaviour.h"

#include "components/RenderingComponent.h"

#include "util/GameTimer.h"

namespace CS418
{
	LuaManager::~LuaManager()
	{
		if (m_pLuaState)
			lua_close(m_pLuaState);
	}

	void LuaManager::Initialize()
	{
		m_pLuaState = luaL_newstate();
		luaL_openlibs(m_pLuaState);

		registerClasses();
	}

	void LuaManager::ExecuteFile(const std::string &file)
	{
		if (luaL_loadfile(m_pLuaState, file.c_str()))
		{
			printf("Could not open script: %s\n", file.c_str());
			return;
		}

		if (lua_pcall(m_pLuaState, 0, 0, 0))
		{
			printf("Failed to execute script: %s\n", file.c_str());
			return;
		}
	}

	LuaRef LuaManager::GetGlobal(const std::string name)
	{
		return getGlobal(m_pLuaState, name.c_str());
	}

	void LuaManager::registerClasses()
	{
		getGlobalNamespace(m_pLuaState)
			.beginClass<VECTOR2F>("Vector2f")
				.addConstructor<void(*) (void) >()
				.addData("x", &VECTOR2F::x, true)
				.addData("y", &VECTOR2F::y, true)
			.endClass()
			.beginClass<VECTOR3F>("Vector3f")
				.addConstructor<void(*) (void) >()
				.addData("x", &VECTOR3F::x, true)
				.addData("y", &VECTOR3F::y, true)
				.addData("z", &VECTOR3F::z, true)
			.endClass()
			.beginClass<VECTOR4F>("Vector4f")
				.addConstructor<void(*) (void) >()
				.addData("x", &VECTOR4F::x, true)
				.addData("y", &VECTOR4F::y, true)
				.addData("z", &VECTOR4F::z, true)
				.addData("w", &VECTOR4F::w, true)
			.endClass();

		getGlobalNamespace(m_pLuaState)
			.beginClass<GameComponent>("GameComponent")
			.endClass()
			.beginClass<GameObject>("GameObject")
				.addFunction("AddComponent", &GameObject::AddComponent)
				.addFunction("RemoveComponent", &GameObject::RemoveComponent)
				.addFunction("GetComponents", &GameObject::GetComponents)
				.addFunction("GetComponentsOfType", &GameObject::GetComponentsOfType)
				.addProperty("transform", &GameObject::Lua_GetTransform, &GameObject::Lua_SetTransform)
			.endClass()
			.beginClass<Transform>("Transform")
				.addData("position", &Transform::Position, true)
				.addData("rotation", &Transform::Rotation, true)
				.addData("scale", &Transform::Scale, true)
			.endClass();

		getGlobalNamespace(m_pLuaState)
			.beginClass<GameTimer>("GameTimer")
				.addProperty("playingTime", &GameTimer::GetPlayingTime)
				.addProperty("totalGameTime", &GameTimer::GetTotalGameTime)
				.addProperty("elapsedTimeSeconds", &GameTimer::GetElapsedTimeInSeconds)
				.addProperty("elapsedTime", &GameTimer::GetElapsedTimeInMillis)
			.endClass();
	}
}