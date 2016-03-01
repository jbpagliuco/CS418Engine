#include "graphics/Texture2DGL.h"

#include <GL/glew.h>

namespace CS418
{
	I32 WrapToGL(TEXTURE_WRAP wrap)
	{
		if (wrap == TEXTURE_WRAP_REPEAT)
			return GL_REPEAT;
		else if (wrap == TEXTURE_WRAP_MIRROREDREPEAT)
			return GL_MIRRORED_REPEAT;
		else if (wrap == TEXTURE_WRAP_CLAMP_EDGE)
			return GL_CLAMP_TO_EDGE;
		else
			return GL_CLAMP_TO_BORDER;
	}
	I32 FilterToGL(TEXTURE_FILTER filter)
	{
		if (filter == TEXTURE_FILTER_LINEAR)
			return GL_LINEAR;
		else
			return GL_NEAREST;
	}
}