#include "lnpch.h"
#include "Material.h"

#include "Lanna/Application.h"
#include "Lanna/Resources.h"

namespace Lanna {
	Material::Material()
	{

	}
	Material::Material(const char* file)
	{

	}
	Material::~Material()
	{

	}

	void Material::setTexture(const char* file)
	{
		m_Type = TEXTURE;
		m_TextureID = LN_RESOURCES.Import<Texture>(file);
	}

	void Material::setColor(glm::vec4 color)
	{
		m_Type = COLOR;
		m_Color = color;
	}

}