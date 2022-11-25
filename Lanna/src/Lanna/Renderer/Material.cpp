#include "lnpch.h"
#include "Material.h"

namespace Lanna {
	Material::Material()
	{
		m_Type = NONE;

	}
	Material::Material(glm::vec4 color): m_Type(COLOR), m_Color(color)
	{

	}
	Material::Material(const char* file): m_Type(TEXTURE)
	{
		m_TexPath = file;
		if (!m_TexPath.empty())
		{
			m_texture = new Texture();
			m_texture->Init(file);
			m_texid = m_texture->GetTextureId();
			m_TexSize = m_texture->GetSize();
		}
	}
	Material::~Material()
	{
	}
	void Material::setTexture(const char* file)
	{
		m_Type = TEXTURE;
		m_TexPath = file;
		/*if (m_texture!=nullptr)
			delete m_texture;*/
		m_texture = new Texture();
		m_texture->Init(file);
		m_texid = m_texture->GetTextureId();
		m_TexSize = m_texture->GetSize();
	}

}