#pragma once

#include "GameComponent.h"

namespace CS418
{
	class RenderingComponent : public GameComponent
	{
	public:
		RenderingComponent(std::string name);
		virtual ~RenderingComponent();

		virtual void Initialize();
		
		virtual void Update();
	};
}