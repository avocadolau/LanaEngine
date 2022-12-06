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
		MaterialComponent(MaterialComponent* copy);
		MaterialComponent(glm::vec4 color);
		MaterialComponent(const char* file);
		~MaterialComponent();

		unsigned int getTextureID();
		Material* getMaterial();
		void setTexture(const char* file);
		void setColor(glm::vec4 color);

		void Use() override;
		void ImGuiDraw() override;
	public:
		//std::string m_TexPath;
		//std::string m_MatPath;
		//glm::vec2 m_TexSize;
		//glm::vec4 m_Color;
		//unsigned int m_texid;
		ResourceId m_MaterialID=-1;
	};
}