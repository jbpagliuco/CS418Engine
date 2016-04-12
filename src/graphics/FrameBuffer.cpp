#include "graphics/FrameBuffer.h"

#include <GL/glew.h>

namespace CS418
{
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_bufferID);
	}

	void FrameBuffer::Initialize(U32 width, U32 height)
	{
		glGenFramebuffers(1, &m_bufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);
		
		m_colorMapID = buildColorMap(width, height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorMapID, 0);

		m_depthMapID = buildDepthMap(width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthMapID);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			printf("Framebuffer not complete\n");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Resize(U32 width, U32 height)
	{
		glDeleteFramebuffers(1, &m_bufferID);

		Initialize(width, height);
	}

	U32 FrameBuffer::GetID()const
	{
		return m_bufferID;
	}

	U32 FrameBuffer::GetColorMap()const
	{
		return m_colorMapID;
	}

	U32 FrameBuffer::GetDepthMap()const
	{
		return m_depthMapID;
	}

	U32 FrameBuffer::buildColorMap(U32 width, U32 height)
	{
		U32 id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		return id;
	}

	U32 FrameBuffer::buildDepthMap(U32 width, U32 height)
	{
		U32 id;
		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		return id;
	}
}