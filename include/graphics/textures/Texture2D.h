#pragma once

#include "util/Util.h"

namespace CS418
{
	class Texture2D
	{
	public:
		virtual ~Texture2D();

		void Initialize(byte * pData, U32 width, U32 height);

		byte * GetData()const;

		U32 GetWidth()const;
		U32 GetHeight()const;

	private:
		byte * m_pData;

		U32 m_width, m_height;
	};
}