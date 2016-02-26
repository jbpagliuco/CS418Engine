#pragma once

#include "util/Util.h"

namespace CS418
{
	struct Viewport
	{
		F32 TopLeftX, TopLeftY;
		F32 Width, Height;
		F32 MinDepth, MaxDepth;
	};
}