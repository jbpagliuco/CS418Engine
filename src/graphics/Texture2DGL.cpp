#include "graphics/Texture2DGL.h"

#include <GL/glew.h>

namespace CS418
{
	TEXTURE_WRAP StringToTextureWrap(const std::string &wrap)
	{
		if (wrap == "REPEAT")
			return TEXTURE_WRAP_REPEAT;
		else if (wrap == "MIRRORED_REPEAT")
			return TEXTURE_WRAP_MIRROREDREPEAT;
		else if (wrap == "CLAMP_EDGE")
			return TEXTURE_WRAP_CLAMP_EDGE;
		else
			return TEXTURE_WRAP_CLAMP_BORDER;
	}
	TEXTURE_FILTER StringToTextureFilter(const std::string &filter)
	{
		if (filter == "LINEAR")
			return TEXTURE_FILTER_LINEAR;
		else
			return TEXTURE_FILTER_NEAREST;
	}

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


	Texture2DGL::~Texture2DGL()
	{

	}

	void Texture2DGL::Initialize(Texture2D * pTex2D, const TEXTURE2D_DESC &texDesc)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapToGL(texDesc.WrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapToGL(texDesc.WrapT));
		if (texDesc.WrapS == TEXTURE_WRAP_CLAMP_BORDER || texDesc.WrapT == TEXTURE_WRAP_CLAMP_BORDER)
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &(texDesc.BorderColor.x));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterToGL(texDesc.FilterMin));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterToGL(texDesc.FilterMag));

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pTex2D->GetWidth(), pTex2D->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, pTex2D->GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	U32 Texture2DGL::GetID()const
	{
		return m_id;
	}
}