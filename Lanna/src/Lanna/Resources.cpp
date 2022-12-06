#include "lnpch.h"
#include "Resources.h"

namespace Lanna {
	std::vector<Resources::Resource*> Resources::m_Resources[Resources::LRT_LAST];

	void Resources::PushResource(ResourceType rt, const char* file, void* rsc)
	{
		Resource* resource = new Resource();

		resource->filePath = file;
		resource->resource = rsc;

		m_Resources[rt].push_back(resource);
		std::string saveFile = GetSavePath(rt, file);
		//std::ofstream outfile(saveFile.c_str());
		std::string message = "Loaded resource \"" + resource->filePath + "\" successfully.";

		LN_CORE_INFO(message.c_str());
	}
	ResourceId Resources::getResourcePosition(ResourceType rt, const char* file)
	{
		size_t size = m_Resources[rt].size();

		ResourceId resourceId = size;

		for (size_t i = 0; i < size; i++) {
			if (m_Resources[rt][i]->filePath == file) {
				resourceId = i;
				break;
			}
		}

		return resourceId;
	}
	std::string Resources::GetSavePath(ResourceType rt,const char* file)
	{
		std::string sPath;

		std::string ext;
		std::string folder = "resources/";

		switch (rt)
		{
		case Lanna::Resources::LRT_TEXTURE:				ext = ".lntexture";		folder += "textures/";		break;
		case Lanna::Resources::LRT_SHADER:				ext = ".lnshader";		folder += "shaders/";		break;
		case Lanna::Resources::LRT_MESH:				ext = ".lnmesh";		folder += "models/";		break;
		case Lanna::Resources::LRT_MATERIAL:			ext = ".lnmaterial";	folder += "materials/";		break;
		case Lanna::Resources::LRT_LAST:				ext = ".error";			break;
		default:										ext = ".error";			break;
		}

		sPath = folder + GetFileName(file) + ext;
		return sPath;
	}
	Resources::Resources()
	{

	}

	Resources::~Resources()
	{
		Clear();
	}

	void Resources::Clear()
	{
		for (int i = 0; i < ResourceType::LRT_LAST; i++)
		{
			m_Resources[i].clear();
		}

		for (int i = 0; i < 10; i++)
		{

		}
	}

}