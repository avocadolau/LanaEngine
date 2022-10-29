#include "lnpch.h"
#include "Framebuffer.h"
namespace Lanna
{


	void Framebuffer::Init(int width, int height)
	{
		this->width = width;
		this->height = height;
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		// Color texture
		glGenTextures(1, &m_ColorBufferTexture);
		glBindTexture(GL_TEXTURE_2D, m_ColorBufferTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBufferTexture, 0);
		// Render buffer object in the future for depth
		glGenRenderbuffers(1, &m_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LN_CORE_FATAL("Framebuffer not compleated");
		}
		else
			LN_CORE_INFO("Framebuffer completed");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Framebuffer::Bind(bool clear)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		if(clear)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Framebuffer::Clear()
	{

		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	}
}