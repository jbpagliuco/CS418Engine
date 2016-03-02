#pragma once

#include "Texture2D.h"
#include "math/Vector.h"

#include <string>

namespace CS418
{
	enum TEXTURE_WRAP
	{
		TEXTURE_WRAP_REPEAT = 0,
		TEXTURE_WRAP_MIRROREDREPEAT,
		TEXTURE_WRAP_CLAMP_EDGE,
		TEXTURE_WRAP_CLAMP_BORDER
	};
	enum TEXTURE_FILTER
	{
		TEXTURE_FILTER_NEAREST = 0,
		TEXTURE_FILTER_LINEAR
	};

	struct TEXTURE2D_DESC
	{
		TEXTURE2D_DESC()
		{
			WrapS = WrapT = TEXTURE_WRAP_REPEAT;
			FilterMin = FilterMag = TEXTURE_FILTER_LINEAR;
			BorderColor = VECTOR4F(0.0f, 0.0f, 0.0f, 1.0f);
		}

		TEXTURE_WRAP WrapS, WrapT;
		TEXTURE_FILTER FilterMin, FilterMag;
		VECTOR4F BorderColor;
	};

	extern TEXTURE_WRAP StringToTextureWrap(const std::string &wrap);
	extern TEXTURE_FILTER StringToTextureFilter(const std::string &filter);

	class Texture2DGL
	{
	public:
		virtual ~Texture2DGL();

		void Initialize(Texture2D * tex2D, const TEXTURE2D_DESC &texDesc);

		U32 GetID()const;

	private:
		U32 m_id;
	};
}