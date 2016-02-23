#include "engine/LuaManager.h"

namespace CS418
{
	LuaManager::~LuaManager()
	{
		if (m_pState)
			lua_close(m_pState);
	}

	void LuaManager::Initialize()
	{
		m_pState = lua_open();
		luaL_openlibs(m_pState);
	}
}