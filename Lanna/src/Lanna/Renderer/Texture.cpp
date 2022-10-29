#include "lnpch.h"
//#include <Lanna/Resources.h>
//
//#include "Lanna/Utilities/Json/JsonDoc.h"
//
//Lanna::Texture::Texture()
//	: m_Type(TextureType::color), m_ResourceId(NULL), m_TextureId(NULL)
//{
//	m_Color = { 0.2, 0.2, 0.2, 1.0 };
//}
//
//Lanna::Texture::Texture(Color4f color)
//	: m_Type(TextureType::color), m_Color(color), m_ResourceId(NULL), m_TextureId(NULL)
//{
//}
//
//Lanna::Texture::Texture(const char* file)
//{
//	JsonDoc matFile(file);
//
//	std::string texturePath = matFile["texture"];
//	m_Color = matFile["color"];
//	m_Type = matFile["type"];
//	if (!texturePath.empty())
//	{
//		m_ResourceId = Resources::Load<Image>(texturePath.c_str());
//		m_TextureId = Resources::GetResourceById<Image>(m_ResourceId)->GetTextureId();
//	}
//}
//
//Lanna::Texture::~Texture()
//{
//}
//
//void Lanna::Texture::setTexture(const char* file)
//{
//	m_ResourceId = Resources::Load<Image>(file);
//	m_TextureId = Resources::GetResourceById<Image>(m_ResourceId)->GetTextureId();
//}