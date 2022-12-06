#include "lnpch.h"
#include "Material.h"

#include "Lanna/Application.h"
#include "Lanna/Resources.h"
#include "Lanna/Utilities/FileHelpers.h"

namespace Lanna {
	Material::Material()
	{
		setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	Material::Material(const char* file)
	{
		if (CheckExtension(GetExtension(file)) == LFT_Texture)
		{
			setTexture(file);
		}
	}
	Material::~Material()
	{

	}

	void Material::setTexture(const char* file)
	{
		m_Type = Type::TEXTURE;
		m_TextureID = LN_RESOURCES.Import<Texture>(file);
	}

	void Material::setColor(glm::vec4 color)
	{
		m_Type = Type::COLOR;
		m_Color = color;
	}

	glm::vec4 Material::GetColor()
	{
		if (m_Type == Type::COLOR)
			return m_Color;
		else
			return glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Texture* Material::GetTexture()
	{
		if (m_Type == Type::TEXTURE)
			return LN_RESOURCES.GetResourceById<Texture>(m_TextureID);
		else
			return nullptr;
	}

	std::string Material::GetTexturePath()
	{
		std::string ret;
		if (m_Type == Type::TEXTURE)
			ret = LN_RESOURCES.GetPathById<Texture>(m_TextureID);
		else
			ret = "no path";
		return ret;
	}

	bool Material::IsColor()
	{
		return m_Type == Type::COLOR;
	}

	bool Material::IsTexture()
	{
		return m_Type == Type::TEXTURE;
	}

	void Material::Save(const char* path)
	{
		ResourceId m_TextureID;
		Type m_Type = NONE;
		glm::vec4 m_Color;
	}

	void Material::Load(const char* path)
	{

	}

}