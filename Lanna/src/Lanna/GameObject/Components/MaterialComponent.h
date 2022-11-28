#pragma once

#include "Lanna/GameObject/Component.h"
#include <glew.h>
#include <glm.hpp>
#include "Lanna/Resources/Texture.h"
#include "Lanna/Resources.h"

namespace Lanna
{
	class MaterialComponent : public Component
	{
	public:
		enum Type
		{
			COLOR,
			TEXTURE,
			NONE
		};
		MaterialComponent();
		MaterialComponent(glm::vec4 color);
		MaterialComponent(const char* file);
		~MaterialComponent();

		unsigned int getTextureID();

		inline Type getType() { return m_Type; }
		inline glm::vec4 getColor() { return m_Color; }
		inline const char* getMaterialPath() { return m_MatPath.c_str(); }
		inline const char* getTexturePath() { return m_TexPath.c_str(); }

		void setTexture(const char* file);
		inline void setColor(glm::vec4 color) { m_Color = color; }
		inline void setType(Type type) { m_Type = type; }
		inline glm::vec2 GetTextureSize() { return m_TexSize; }

		void Use() override;
		void ImGuiDraw() override;
	private:
		std::string m_TexPath;
		std::string m_MatPath;
		glm::vec2 m_TexSize;
		glm::vec4 m_Color;
		Type m_Type;
		unsigned int m_texid;
		ResourceId m_TextureID;
	};
}