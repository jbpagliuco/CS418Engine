#pragma once

#include "Texture2D.h"
#include "math/Vector.h"

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
		TEXTURE_WRAP wrapS, wrapT;
		TEXTURE_FILTER filterMin, filterMag;
		VECTOR4F * pBorderColor;
	};

	class Texture2DGL
	{
	public:
		virtual ~Texture2DGL();

		void Initialize(const Texture2D &tex2D, const TEXTURE2D_DESC &texDesc);

		U32 GetID()const;

	private:
		U32 m_id;
	};
}