#pragma once

#include "util/Util.h"

namespace CS418
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		virtual ~FrameBuffer();

		void Initialize(U32 width, U32 height, bool depthOnly);

		void Resize(U32 width, U32 height);

		U32 GetID()const;
		U32 GetColorMap()const;
		U32 GetDepthMap()const;

	private:
		U32 buildColorMap(U32 width, U32 height);
		U32 buildDepthMap(U32 width, U32 height, bool depthOnly);

	private:
		U32 m_bufferID;
		U32 m_colorMapID;
		U32 m_depthMapID;
		bool m_depthOnly;
	};
}