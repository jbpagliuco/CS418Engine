#include "content/TextureLoader.h"

#include <GL/glew.h>
#include <SOIL.h>

namespace CS418
{
	

	Texture2D * LoadTexture2D(const std::string &filepath)
	{
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapToGL(desc.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapToGL(desc.wrapT));
		if (desc.wrapS == TEXTURE_WRAP_CLAMP_BORDER || desc.wrapT == TEXTURE_WRAP_CLAMP_BORDER)
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &(desc.pColor->x));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterToGL(desc.filterMin));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterToGL(desc.filterMag));
		*/
		I32 width, height;
		byte * imageData = SOIL_load_image(filepath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

		Texture2D * pTex2D = new Texture2D;
		pTex2D->Initialize(imageData, width, height);
		
		return pTex2D;
	}
}