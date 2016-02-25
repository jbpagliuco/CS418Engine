#pragma once

#include "GameComponent.h"

namespace CS418
{
	class Behaviour : public GameComponent
	{
	public:
		Behaviour(const std::string &type = "Behaviour");
		virtual ~Behaviour();

	public:
		bool Enabled;

	protected:
		std::string m_type;
	};
}