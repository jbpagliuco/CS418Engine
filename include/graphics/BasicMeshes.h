#pragma once

#include "Mesh.h"

namespace CS418
{
	Mesh CreateQuad();
	Mesh CreateCube();
	Mesh CreateSphere(F32 radius, U32 sclices, U32 stacks);
}