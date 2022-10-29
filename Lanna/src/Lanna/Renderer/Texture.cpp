#include "lnpch.h"
//#include <Lanna/Resources.h>
//
//#include <Lanna/utilities/json/JSONDocument.h>
//
//Lanna::Material::Material()
//	: m_Type(MaterialType::color), m_ResourceId(NULL), m_TextureId(NULL)
//{
//	m_Color = { 0.2, 0.2, 0.2, 1.0 };
//}
//
//Lanna::Material::Material(Color4f color)
//	: m_Type(MaterialType::color), m_Color(color), m_ResourceId(NULL), m_TextureId(NULL)
//{
//}
//
//Lanna::Material::Material(const char* file)
//{
//	JSONDocument matFile(file);
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
//Lanna::Material::~Material()
//{
//}
//
//void Lanna::Material::setTexture(const char* file)
//{
//	m_ResourceId = Resources::Load<Image>(file);
//	m_TextureId = Resources::GetResourceById<Image>(m_ResourceId)->GetTextureId();
//}