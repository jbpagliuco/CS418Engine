#pragma once

#include <lua.hpp>

namespace CS418
{
	class LuaManager
	{
		virtual ~LuaManager();

		void Initialize();

		lua_State * m_pState;
	};
}