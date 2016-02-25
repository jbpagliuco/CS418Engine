#pragma once

#include <LuaBridge.h>
#include <lua.hpp>
#include <string>

namespace CS418
{
	class LuaManager
	{
	public:
		virtual ~LuaManager();

		void Initialize();

		void ExecuteFile(const std::string &file);

		template <typename T>
		void Push(const std::string name, T &value);

		luabridge::LuaRef GetGlobal(const std::string name);

	private:
		void registerClasses();

	private:
		lua_State * m_pLuaState;
	};

	template <typename T>
	void LuaManager::Push(const std::string name, T &value)
	{
		luabridge::push(m_pLuaState, &value);
		lua_setglobal(m_pLuaState, name.c_str());
	}
}