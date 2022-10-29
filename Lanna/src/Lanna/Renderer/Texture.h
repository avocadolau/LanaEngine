#pragma once

#include <string>

namespace Lanna {

	typedef size_t ResourceId;

	class LN_API Texture
	{
	public:
		enum TextureType
		{
			textured,
			color
		};
		Texture();
		Texture(Color4f color);
		Texture(const char* file);
		~Texture();

		inline MaterialType getType() { return m_Type; }
		inline uint32_t getTextureId() { return m_TextureId; }
		inline uint32_t getResourceId() { return m_ResourceId; }
		inline Color4f getColor() { return m_Color; }

		void setTexture(const char* file);
		inline void setColor(Color4f color) { color = m_Color; }

	private:
		ResourceId m_ResourceId;
		uint32_t m_TextureId;
		Color4f m_Color;
		MaterialType m_Type;
	};

}
