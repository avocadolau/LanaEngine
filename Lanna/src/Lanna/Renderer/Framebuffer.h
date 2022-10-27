#pragma once

#include "lnpch.h"
#include "Lanna/Log.h"
#include <glew.h>
#include <glm.hpp>

namespace Lanna
{
	class LANNA_API Framebuffer
	{
	public:
		unsigned int fbo;
		unsigned int textureColorbuffer;
		unsigned int rbo;
	public:

		Framebuffer()
		{

		}
		~Framebuffer()
		{
		}
		void Init(int width, int height)
		{
			glGenFramebuffers(1, &fbo);


			// color atatchment
			glGenTextures(1, &textureColorbuffer);
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

			// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

			// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LN_INFO("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		}
		void Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}
		void Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void Clear()
		{
			glDeleteFramebuffers(1, &fbo);
		}
	};
}
