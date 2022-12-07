#include "lnpch.h"
#include "Material.h"

#include "Lanna/Application.h"
#include "Lanna/Resources.h"
#include "Texture.h"
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
		std::fstream file;

		// clear file
		file.open(path, std::ofstream::out | std::ofstream::trunc);
		file.close();

		// write
		file.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

		file.write((const sbyte*)&m_Type, sizeof(Type));
		if (m_Type == Type::COLOR)
		{
			file.write((const sbyte*)&m_Color, sizeof(glm::vec4));

		}
		if (m_Type == Type::TEXTURE)
		{
			std::string savepath = LN_RESOURCES.GetPathById<Texture>(m_TextureID);
			size_t sizepath = sizeof(savepath);
			file.write((const sbyte*)&sizepath, sizeof(size_t));
			file.write((const sbyte*)&savepath, sizepath);

		}


		file.close();

		std::string message = "saved succesfully as: ";
		message.append(path);
		LN_CORE_INFO(message.c_str());
		LN_INFO(message.c_str());
	}

	void Material::Load(const char* path)
	{
		std::fstream file;

		// read
		file.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

		if (file.is_open())
		{
			file.read((sbyte*)&m_Type, sizeof(Type));


			if (m_Type == Type::COLOR)
			{
				file.read((sbyte*)&m_Color, sizeof(glm::vec4));

			}
			if (m_Type == Type::TEXTURE)
			{
				std::string savepath;
				size_t sizepath;
				file.read((sbyte*)&sizepath, sizeof(size_t));
				file.read((sbyte*)&savepath, sizepath);

				if (savepath.c_str() != "")
				{
					m_TextureID = LN_RESOURCES.Import<Texture>(savepath.c_str());
				}
			}
		}

		file.close();
		std::string message = path;
		message.append(" loaded succesfuly");
		LN_CORE_INFO(message.c_str());
		LN_INFO(message.c_str());
	}

}