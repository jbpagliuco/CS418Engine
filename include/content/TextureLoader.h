#pragma once

#include <string>

#include "graphics/textures/Texture2D.h"
#include "math/Vector.h"

namespace CS418
{
	

	extern Texture2D * LoadTexture2D(const std::string &filepath);
}