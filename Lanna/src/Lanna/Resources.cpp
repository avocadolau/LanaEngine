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