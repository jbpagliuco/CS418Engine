#include "System.h"

namespace CS418
{
	System::~System()
	{

	}

	void System::Initialize()
	{
		m_gfx.Initialize();
		m_game.Initialize();
	}

	int System::Update()
	{
		m_gfx.BeginScene();
		m_gfx.EndScene();

		return 0;
	}
}