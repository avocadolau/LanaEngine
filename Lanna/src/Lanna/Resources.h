#pragma once
#pragma warning(disable : 4251)

#include <Lanna/Core.h>

// Resources
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Lanna/Resources/AllAssets.h"

#include <string>
#include <vector>

typedef size_t ResourceId;

namespace Lanna {
	class LANNA_API Resources
	{
	public:
		// Enum that indicates all the resources that can be loaded by the engine
		enum ResourceType {
			LRT_IMAGE,
			LRT_SHADER,
			LRT_MODEL,
			LRT_TEXTURE,
			LRT_LAST
		};

		struct Resource {
			// Path to resource
			std::string filePath;

			// Any type
			void* resource;
		};
	private:
		Resources();

		static std::vector<Resource*> m_Resources[LRT_LAST];

		static void PushResource(ResourceType rt, const char* file, void* rsc);
		static ResourceId getResourcePosition(ResourceType rt, const char* file);
	public:
		template<class T> static ResourceId Import(const char* file);
		template<class T> static ResourceId Save();
		template<class T> static ResourceId Load();
		template<class T> static T* GetResourceById(ResourceId id);

		static void Clear();
	};

	// SPECIALIZATION FOR SHADER
	template<>
	inline ResourceId Resources::Import<Shader>(const char* file) {
		ResourceId position = getResourcePosition(LRT_SHADER, file);
		size_t size = m_Resources[LRT_SHADER].size();

		ResourceId resourceId;
		 
		if (position == size) {
			Shader* shader = new Shader();
			shader->Init(file);

			PushResource(LRT_SHADER, file, shader);

			resourceId = size;
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}

	template<>
	inline Shader* Resources::GetResourceById<Shader>(ResourceId id) {
		Shader* resource = NULL;

		if (id >= 0 && id < m_Resources[LRT_SHADER].size()) {
			resource = static_cast<Shader*>(m_Resources[LRT_SHADER][id]->resource);
		}

		return resource;
	}

	//--SPECIALIZATION FOR SPRITE
	template<>
	inline ResourceId Resources::Load<Image>(const char * file)
	{
		ResourceId position = getResourcePosition(WRT_IMAGE, file);
		size_t size = m_Resources[WRT_IMAGE].size();

		ResourceId resourceId;

		if (position == size) {
			Image* image = new Image();
			image->Init(file);

			PushResource(WRT_IMAGE, file, image);

			resourceId = size;
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}

	/*template<>
	inline Image* Resources::GetResourceById<Image>(ResourceId id)
	{
		Image* image = NULL;
	
		if (id >= 0 && id < m_Resources[LRT_IMAGE].size()) {
			image = static_cast<Image*>(m_Resources[LRT_IMAGE][id]->resource);
		}
	
		return image;
	}*/
	//--SPECIALIZATION FOR MODEL
	template<>
	inline ResourceId Resources::Load<Model>(const char* file)
	{
		ResourceId position = getResourcePosition(LRT_MODEL, file);
		size_t size = m_Resources[LRT_MODEL].size();

		ResourceId resourceId;

		if (position == size) {
			Model* model = new Model(file);

			PushResource(LRT_MODEL, file, model);

			resourceId = size;
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}
	/*template<>
	inline Model* Resources::GetResourceById<Model>(ResourceId id)
	{
		Model* model = NULL;

		if (id >= 0 && id < m_Resources[WRT_MODEL].size()) {
			model = static_cast<Model*>(m_Resources[WRT_MODEL][id]->resource);
		}

		return model;
	}*/
	template<>
	inline ResourceId Resources::Import<Texture>(const char* file)
	{
		ResourceId position = getResourcePosition(LRT_TEXTURE, file);
		size_t size = m_Resources[LRT_TEXTURE].size();

		ResourceId resourceId;

		if (position == size) {
			Texture* texture = new Texture(file);

			PushResource(LRT_TEXTURE, file, texture);

			resourceId = size;
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}
	template<>
	inline Lanna::Texture* Resources::GetResourceById<Lanna::Texture>(ResourceId id)
	{
		Lanna::Texture* material = NULL;

		if (id >= 0 && id < m_Resources[LRT_TEXTURE].size()) {
			material = static_cast<Lanna::Texture*>(m_Resources[LRT_TEXTURE][id]->resource);
		}

		return material;
	}
}