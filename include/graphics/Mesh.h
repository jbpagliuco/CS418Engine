#pragma once

#include "Util.h"

namespace CS418
{
	class Mesh
	{
	public:
		virtual ~Mesh();

		void Draw();

	private:
		U32 m_VB;
		U32 m_IB;
		U32 m_VAO;
	};
}