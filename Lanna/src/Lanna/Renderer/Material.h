#pragma once
#include "Lanna/Renderer/Texture.h"

namespace Lanna
{
	class Material
	{
	public:
		enum Type
		{
			COLOR,
			TEXTURE,
			NONE
		};
		Material();
		Material(glm::vec4 color);
		Material(const char* file);
		~Material();

		inline unsigned int getTextureID() { return m_texid; }

		inline Type getType() { return m_Type; }
		inline glm::vec4 getColor() { return m_Color; }
		inline const char* getMaterialPath() { return m_MatPath.c_str(); }
		inline const char* getTexturePath() { return m_TexPath.c_str(); }

		void setTexture(const char* file);
		inline void setColor(glm::vec4 color) { m_Color = color; }
		inline void setType(Type type) { m_Type = type; }
		inline glm::vec2 GetTextureSize() { return m_TexSize; }

	private:
		std::string m_TexPath;
		std::string m_MatPath;
		glm::vec2 m_TexSize;
		glm::vec4 m_Color;
		Type m_Type;
		Texture* m_texture;
		unsigned int m_texid;
	};
}
