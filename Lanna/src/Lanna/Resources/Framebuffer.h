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
		uint32_t m_FBO;
		uint32_t m_ColorBufferTexture;
		uint32_t m_RBO;
		uint32_t width, height;

	public:

		Framebuffer()
		{

		}
		~Framebuffer()
		{
		}
		void Init(int width, int height);

		void Bind(bool clear);
		void Unbind();
		void Clear();

		inline uint32_t getColorBufferTexture() { return m_ColorBufferTexture; }
	};
}
