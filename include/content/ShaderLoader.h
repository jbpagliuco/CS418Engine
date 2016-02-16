#pragma once

#include "graphics\ShaderProgram.h"

namespace CS418
{
	extern ShaderProgram * LoadShader(const std::string &vertexShaderFilepath, const std::string &fragShaderFilepath);
}