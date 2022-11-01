#pragma once

#include <Lanna/Core.h>

#include <glew.h>
#include <glm.hpp>

#include <string>

namespace Lanna {

	class LANNA_API Texture
	{
	private:
		unsigned int m_id;
		glm::vec2 m_size;
		int m_channels;

	public:
		
		Texture();
		~Texture();

		bool Init(const char* path);

		int GetTextureId() { return m_id; }
		int GetChannels() { return m_channels; }

		int GetWidth() { return m_size.x; }
		int GetHeight() { return m_size.y; }
		glm::vec2 GetSize() { return m_size; }
	};

}
