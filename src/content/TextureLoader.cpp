#include "content/TextureLoader.h"

#include <SOIL.h>

namespace CS418
{
	

	Texture2D * LoadTexture2D(const std::string &filepath)
	{		
		I32 width, height;
		byte * imageData = SOIL_load_image(filepath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

		Texture2D * pTex2D = new Texture2D;
		pTex2D->Initialize(imageData, width, height);
		
		return pTex2D;
	}
}