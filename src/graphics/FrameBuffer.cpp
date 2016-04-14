#include "graphics/FrameBuffer.h"

#include <GL/glew.h>

namespace CS418
{
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_bufferID);
	}

	void FrameBuffer::Initialize(U32 width, U32 height, bool depthOnly)
	{
		m_depthOnly = depthOnly;

		glGenFramebuffers(1, &m_bufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);
		
		m_colorMapID = buildColorMap(width, height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorMapID, 0);
		m_depthMapID = buildDepthMap(width, height, false);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapID, 0);
		

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			printf("Framebuffer not complete\n");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Resize(U32 width, U32 height)
	{
		glDeleteFramebuffers(1, &m_bufferID);

		Initialize(width, height, m_depthOnly);
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

	U32 FrameBuffer::buildDepthMap(U32 width, U32 height, bool depthOnly)
	{
		U32 id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

		return id;
	}
}