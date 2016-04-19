#include "graphics/textures/Texture2D.h"

namespace CS418
{
	Texture2D::~Texture2D()
	{

	}

	void Texture2D::Initialize(byte * pData, U32 width, U32 height)
	{
		m_pData = pData;

		m_width = width;
		m_height = height;
	}

	byte * Texture2D::GetData()const
	{
		return m_pData;
	}

	U32 Texture2D::GetWidth()const
	{
		return m_width;
	}

	U32 Texture2D::GetHeight()const
	{
		return m_height;
	}
}