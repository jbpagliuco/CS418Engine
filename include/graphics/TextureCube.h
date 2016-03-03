#pragma once

#include "Texture2D.h"

namespace CS418
{
	class TextureCube
	{
	public:
		virtual ~TextureCube();

		void Initialize(Texture2D ** pTextures);

		U32 GetID()const;

	private:
		U32 m_id;
	};
}