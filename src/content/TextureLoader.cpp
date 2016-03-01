#include "content/TextureLoader.h"

#include <GL/glew.h>
#include <SOIL.h>

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

	Texture2D * LoadTexture2D(const std::string &filepath)
	{
		U32 id;
		glGenTextures(1, &id);		
		glBindTexture(GL_TEXTURE_2D, id);
		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapToGL(desc.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapToGL(desc.wrapT));
		if (desc.wrapS == TEXTURE_WRAP_CLAMP_BORDER || desc.wrapT == TEXTURE_WRAP_CLAMP_BORDER)
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &(desc.pColor->x));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterToGL(desc.filterMin));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterToGL(desc.filterMag));












		I32 width, height;
		byte * imageData = SOIL_load_image(filepath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(imageData);
		glBindTexture(GL_TEXTURE_2D, 0);

		Texture2D * pTex2D = new Texture2D;
		pTex2D->Initialize();
		
		return pTex2D;
	}
}