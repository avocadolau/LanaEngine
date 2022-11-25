#include "lnpch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <glew.h>
#include <glm.hpp>
#include <stb_image.h>

namespace Lanna{

	Texture::Texture()
	{

	}

	Texture::~Texture()
	{
	}

	bool Texture::Init(const char* path)
	{
		int x, y, ch;

		unsigned char* image = stbi_load(path, &x, &y, &ch, STBI_rgb_alpha);

		if (!image) {
			return false;
		}

		glGenTextures(1, &m_buffID);
		glBindTexture(GL_TEXTURE_2D, m_buffID);

		int PicType = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, PicType, x, y, 0, PicType, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);

		m_size.x = x;
		m_size.y = y;
		m_channels = ch;

		return true;
	}


}