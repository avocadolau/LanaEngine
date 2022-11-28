#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include <glew.h>
#include <glm.hpp>
#include "Lanna/Resources/Texture.h"

typedef size_t ResourceId;

namespace Lanna {
	class Material
	{
	public:
		enum Type
		{
			COLOR,
			TEXTURE,
			NONE
		};

		Texture* m_Texture;
		ResourceId m_TextureID;
		Type m_Type;
		glm::vec4 m_Color;

	public:
		Material();
		Material(const char* file);
		~Material();

		void setTexture(const char* file);
		void setColor(glm::vec4 color);
	};
}
#endif