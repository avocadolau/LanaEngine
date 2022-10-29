#pragma once

#include <Lanna/Core.h>

#include <Lanna/Utilities/Maths/Vector4f.h>
#include <Lanna/Utilities/Maths/Vector3f.h>
#include <Lanna/Utilities/Maths/Vector2i.h>

#include <string>

namespace Lanna {

	typedef size_t ResourceId;

	class LANNA_API Texture
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

		inline TextureType getType() { return m_Type; }
		inline uint32_t getTextureId() { return m_TextureId; }
		inline uint32_t getResourceId() { return m_ResourceId; }
		inline Color4f getColor() { return m_Color; }

		void setTexture(const char* file);
		inline void setColor(Color4f color) { color = m_Color; }

	private:
		ResourceId m_ResourceId;
		uint32_t m_TextureId;
		Color4f m_Color;
		TextureType m_Type;
	};

}
