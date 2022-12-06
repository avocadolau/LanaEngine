#include "lnpch.h"
#include "Lanna/Application.h"
#include "Resources.h"
#include "imgui.h"
#include "Lanna/Utilities/FileDialog.h"

namespace Lanna {
	std::vector<Resources::Resource*> Resources::m_Resources[Resources::LRT_LAST];

	void Resources::PushResource(ResourceType rt, const char* file, void* rsc)
	{
		Resource* resource = new Resource();

		resource->filePath = GenerateSavePath(rt, file);;
		resource->resource = rsc;

		m_Resources[rt].push_back(resource);
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

	ResourceId Resources::SelectResourcePopUp(ResourceType rt, bool reset)
	{

		static int selection = -1;

		size_t size = m_Resources[rt].size();

		for (size_t i = 0; i < size; i++) {
			if (ImGui::Selectable(GetFileName(m_Resources[rt][i]->filePath.c_str()).c_str(), selection == i))
			{
				selection = NULL;
				return (ResourceId)i;
			}
		}
		if (ImGui::Selectable("none", selection == -1))
		{
			return (ResourceId)-1;
		}
		return -1;
	}



	std::string Resources::GenerateSavePath(ResourceType rt,const char* file)
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