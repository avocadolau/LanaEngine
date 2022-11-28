#pragma once
#pragma warning(disable : 4251)

#ifndef RESOURCES_H
#define RESOURCES_H


#include <Lanna/Core.h>
#include "Utilities/FileHelpers.h"

// Resources
#include "Resources/Shader.h"
#include "Resources/Texture.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"

#include <string>
#include <vector>

#define RESOURCE_TEST

typedef size_t ResourceId;

namespace Lanna {


	class LANNA_API Resources
	{
	public:
		// Enum that indicates all the resources that can be loaded by the engine
		enum ResourceType {
			LRT_TEXTURE,
			LRT_SHADER,
			LRT_MESH,
			LRT_MATERIAL,
			LRT_LAST
		};

		struct Resource {
			std::string filePath;
			void* resource;
		};

	private:

		static std::vector<Resource*> m_Resources[LRT_LAST];

		static void PushResource(ResourceType rt, const char* file, void* rsc);
		static ResourceId getResourcePosition(ResourceType rt, const char* file);
	public:
		Resources();
		~Resources();

		template<class T> static ResourceId Import(const char* file);
		template<class T> static ResourceId Save(const char* path);
		template<class T> static ResourceId Load(const char* path);
		template<class T> static T* GetResourceById(ResourceId id);

		template<class T> static std::string GetPathById(ResourceId id);
		static void Clear();
	};

	// SPECIALIZATION FOR SHADER
	template<>
	inline ResourceId Resources::Import<Shader>(const char* file) {
		ResourceId position = getResourcePosition(LRT_SHADER, file);
		size_t size = m_Resources[LRT_SHADER].size();

		ResourceId resourceId;
		 
		if (position == size) {
			Shader* shader = new Shader(file);
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

	template<>
	inline std::string Resources::GetPathById<Shader>(ResourceId id) {
		std::string path;
		if (id >= 0 && id < m_Resources[LRT_SHADER].size()) {
			path = m_Resources[LRT_SHADER][id]->filePath;
		}
		return path;
	}

	//--SPECIALIZATION FOR SPRITE
	template<>
	inline ResourceId Resources::Import<Texture>(const char * file)
	{
		ResourceId position = getResourcePosition(LRT_TEXTURE, file);
		size_t size = m_Resources[LRT_TEXTURE].size();

		ResourceId resourceId;

		if (position == size) {
			Texture* image = new Texture();
			image->Init(file);

			PushResource(LRT_TEXTURE, file, image);

			resourceId = size;
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}

	template<>
	inline Texture* Resources::GetResourceById<Texture>(ResourceId id)
	{
		Texture* image = NULL;
	
		if (id >= 0 && id < m_Resources[LRT_TEXTURE].size()) {
			image = static_cast<Texture*>(m_Resources[LRT_TEXTURE][id]->resource);
		}
	
		return image;
	}

	template<>
	inline std::string Resources::GetPathById<Texture>(ResourceId id) {
		std::string path;
		if (id >= 0 && id < m_Resources[LRT_TEXTURE].size()) {
			path = m_Resources[LRT_TEXTURE][id]->filePath;
		}
		return path;
	}

	//--SPECIALIZATION FOR MODEL
	template<>
	inline ResourceId Resources::Import<Mesh>(const char* file)
	{
		ResourceId position = getResourcePosition(LRT_MESH, file);
		size_t size = m_Resources[LRT_MESH].size();

		ResourceId resourceId;

		if (position == size) {
			Mesh* model = new Mesh(file);

			PushResource(LRT_MESH, file, model);

			resourceId = size;
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}
	template<>
	inline Mesh* Resources::GetResourceById<Mesh>(ResourceId id)
	{
		Mesh* model = NULL;

		if (id >= 0 && id < m_Resources[LRT_MESH].size()) {
			model = static_cast<Mesh*>(m_Resources[LRT_MESH][id]->resource);
		}

		return model;
	}
	template<>
	inline std::string Resources::GetPathById<Mesh>(ResourceId id) {
		std::string path;
		if (id >= 0 && id < m_Resources[LRT_MESH].size()) {
			path = m_Resources[LRT_MESH][id]->filePath;
		}
		return path;
	}

	template<>
	inline ResourceId Resources::Import<Material>(const char* file)
	{
		ResourceId position = getResourcePosition(LRT_MATERIAL, file);
		size_t size = m_Resources[LRT_MATERIAL].size();

		ResourceId resourceId;

		if (position == size) {

			Material* material = new Material(file);


			PushResource(LRT_MATERIAL, file, material);

			resourceId = size;
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}
	template<>
	inline Lanna::Material* Resources::GetResourceById<Material>(ResourceId id)
	{
		Lanna::Material* material = NULL;

		if (id >= 0 && id < m_Resources[LRT_MATERIAL].size()) {
			material = static_cast<Lanna::Material*>(m_Resources[LRT_MATERIAL][id]->resource);
		}

		return material;
	}

	
}
#endif // !RESOURCES_H
