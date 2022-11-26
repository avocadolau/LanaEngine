#include "lnpch.h"
#include "Material.h"
#include "Lanna/Resources.h"
#include "Lanna/Application.h"
#include "Lanna/Renderer/Texture.h"

namespace Lanna {

	Material::Material()
	{
		m_Type = Type::COLOR_;
		m_Color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
	}

	Material::Material(const char* file)
	{
		m_Type = Type::COLOR_;
		m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	Material::~Material()
	{

	}

	bool Material::setTexture(Texture* tex)
	{
		if (tex)
		{
			m_Type = Type::TEXTURE_;
			m_Tex = tex;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Material::setColor(glm::vec4 color)
	{
		m_Type = Type::COLOR_;
		m_Color = color;
	}

}