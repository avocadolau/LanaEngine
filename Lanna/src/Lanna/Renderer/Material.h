#pragma once

#include <glew.h>
#include <glm.hpp>
#include "Lanna/Resources.h"

namespace Lanna {

	class Material
	{
	public:
		enum Type
		{
			COLOR_,
			TEXTURE_,
			NONE_
		};
		Material();
		Material(const char* file);
		~Material();

		Type getType() { return m_Type; }
		glm::vec4 getColor() { return m_Color; }

		bool setTexture(Texture* tex);
		void setColor(glm::vec4 color);
		void setType(Type type) { m_Type = type; }
		//inline glm::vec2 GetTextureSize() { return m_TexSize; }

	public:
		glm::vec4 m_Color;
		Texture* m_Tex;
		Type m_Type;

	};

}