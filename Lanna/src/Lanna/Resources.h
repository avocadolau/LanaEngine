#pragma once
#pragma warning(disable : 4251)

#ifndef RESOURCES_H
#define RESOURCES_H


#include <Lanna/Core.h>
#include "Lanna/Log.h"
#include "Utilities/FileHelpers.h"

// Resources
#include "Resources/Shader.h"
#include "Resources/Texture.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"
#include "Resources/Animation.h"
#include "Resources/Skeleton.h"

//#include "Lanna/Resources/Importers/MeshImporter.h"

#include <string>
#include <vector>

#define RESOURCE_TEST

typedef size_t ResourceId;
typedef char sbyte;

struct aiAnimation;


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
			LRT_ANIMATION,
			LRT_SKELETON,
			LRT_LAST
		};

		

		struct Resource {
			std::string filePath;
			void* resource;
		};
		//MeshImporter meshimporter;
	private:

		static std::vector<Resource*> m_Resources[LRT_LAST];

		static void PushResource(ResourceType rt, const char* file, void* rsc);
		static ResourceId getResourcePosition(ResourceType rt, const char* file);
	public:
		Resources();
		~Resources();

		std::vector<Resource*>* GetList(ResourceType rt) { return &m_Resources[rt]; }
		ResourceId PushEmptyResource(ResourceType rt);

		template<class T> static ResourceId Import(const char* file);
		template<class T> static void Save(ResourceId id);
		template<class T> static ResourceId Load(ResourceId id,const char* path);
		template<class T> static T* GetResourceById(ResourceId id);

		template<class T> static std::string GetPathById(ResourceId id);
		//template<class T> static ResourceId DuplicateResource(ResourceId copy);

		ResourceId SelectResourcePopUp(ResourceType rt, bool reset);

		static std::string GenerateSavePath(ResourceType rt, const char* file);
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
		else path = "null";
		return path;
	}

	//--SPECIALIZATION FOR SPRITE
	template<>
	inline ResourceId Resources::Import<Texture>(const char * file)
	{
		/*if (file)
		{
			if (CheckExtension(GetExtension(file)) != FileType::LFT_Texture)
			{
				std::string message = GetExtension(file) + " isnt a texture. Could not import";
				LN_WARN(message.c_str());
				return -1;
			}
		}*/
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
		else path = "null";
		return path;
	}

	//--SPECIALIZATION FOR MODEL
	template<>
	inline ResourceId Resources::Import<Mesh>(const char* file)
	{
		if (file!=nullptr)
		{
			std::string ext = GetExtension(file);

			if (ext != std::string(".fbx") && ext != std::string(".FBX") && ext != std::string(".dae") && ext != std::string(".DAE"))
			{
				std::string message = GetExtension(file) + " isnt a mesh. Could not import";
				LN_WARN(message.c_str());
				return -1;
			}
		}
		ResourceId position = getResourcePosition(LRT_MESH, file);
		size_t size = m_Resources[LRT_MESH].size();

		ResourceId resourceId;

		if (position == size) {
			Mesh* model;
			if (file == nullptr)
			{
				model = new Mesh();
			}
			else if (GetExtension(file).c_str() == ".lnmesh")
			{
				model = new Mesh();
				model->Load(file);
			}
			else
			{
				model = new Mesh(file);
			}



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
		else path = "null";

		return path;
	}
	template<>
	inline void Resources::Save<Mesh>(ResourceId id)
	{
		Mesh* mesh = GetResourceById<Mesh>(id);
		std::string sPath = GetPathById<Mesh>(id);// GenerateSavePath(ResourceType::LRT_MESH, GetPathById<Mesh>(id).c_str());
		//std::fstream write_file;

		//write_file.open(sPath.c_str(), std::fstream::out | std::fstream::binary);
		
		mesh->Save(sPath.c_str());

		//write_file.close();
	}
	template<>
	inline ResourceId Resources::Load<Mesh>(ResourceId id, const char* file)
	{
		if (GetExtension(file).c_str() != "lnmesh")
		{
			LN_WARN("incompatible extension");
		}
		else
		{
			Mesh* mesh = GetResourceById<Mesh>(id);
			//std::string sPath = GetPathById<Mesh>(id);

			mesh->Load(file);
		}
		
		return id;
	}
	template<>
	inline ResourceId Resources::Import<Material>(const char* file)
	{
		if (file)
		{
			if (GetExtension(file) == ".lnmaterial")
			{

			}
			else if (CheckExtension(GetExtension(file)) != FileType::LFT_Texture)
			{
				std::string message = GetExtension(file) + " isnt a texture or material. Could not import";
				LN_WARN(message.c_str());
				return -1;
			}
		}
		ResourceId position = getResourcePosition(LRT_MATERIAL, file);
		size_t size = m_Resources[LRT_MATERIAL].size();

		ResourceId resourceId;

		if (position == size) {

			Material* material;
			if (file == "null")
			{
				material = new Material();
			}
			else if (GetExtension(file).c_str() == ".lnmaterial")
			{
				material = new Material();
				material->Load(file);
			}
			else
			{
				material = new Material(file);
			}

			if (file == "null")
			{
				PushResource(LRT_MATERIAL, "Color material", material);
			}
			else
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

	template<>
	inline std::string Resources::GetPathById<Material>(ResourceId id) {
		std::string path;
		if (id >= 0 && id < m_Resources[LRT_MATERIAL].size()) {
			path = m_Resources[LRT_MATERIAL][id]->filePath;
		}
		else path = "null";
		return path;
	}
	template<>
	inline void Resources::Save<Material>(ResourceId id)
	{
		Material* mat = GetResourceById<Material>(id);
		std::string sPath = GetPathById<Mesh>(id);// GenerateSavePath(ResourceType::LRT_MESH, GetPathById<Mesh>(id).c_str());
		//std::fstream write_file;

		//write_file.open(sPath.c_str(), std::fstream::out | std::fstream::binary);

		mat->Save(sPath.c_str());

		//write_file.close();
	}

	template<>
	inline ResourceId Resources::Load<Material>(ResourceId id, const char* file)
	{
		if (GetExtension(file).c_str() != "lnmaterial")
		{
			LN_WARN("incompatible extension");
		}
		else
		{
			Material* mat = GetResourceById<Material>(id);
			mat->Save(file);
		}
		

		//write_file.close();
		return id;
	}

	template<>
	inline ResourceId Resources::Import<Animation>(const char* file)
	{
		
		if (file)
		{
			/*if (GetExtension(file) == ".lnanimation")
			{

			}
			else if (CheckExtension(GetExtension(file)) != FileType::LFT_Animation)
			{
				std::string message = GetExtension(file) + " isnt an animation. Could not import";
				LN_WARN(message.c_str());
				return -1;
			}*/
		}
		ResourceId position = getResourcePosition(LRT_ANIMATION, file);
		size_t size = m_Resources[LRT_ANIMATION].size();

		ResourceId resourceId;

		if (position == size) {

			Animation* animation;
			if (file == "null")
			{
				animation = new Animation();
			}
			else if (GetExtension(file).c_str() == ".lnanimation")
			{
				animation = new Animation();
				animation->Import(file);
			}
			else
			{
				animation = new Animation();
				animation->Import(file);
			}

			if (file == "null")
			{
				PushResource(LRT_ANIMATION, "animation", animation);
			}
			else
				PushResource(LRT_ANIMATION, file, animation);

			resourceId = size;
		}
		else {
			resourceId = position;
		}
		return resourceId;
	}
	template<>
	inline void Resources::Save<Animation>(ResourceId id)
	{

	}
	template<>
	inline ResourceId Resources::Load<Animation>(ResourceId id, const char* path)
	{

	}
	template<>
	inline Animation* Resources::GetResourceById<Animation>(ResourceId id)
	{
		Lanna::Animation* ani = NULL;

		if (id >= 0 && id < m_Resources[LRT_ANIMATION].size()) {
			ani = static_cast<Lanna::Animation*>(m_Resources[LRT_ANIMATION][id]->resource);
		}

		return ani;
	}
	template<>
	inline std::string Resources::GetPathById<Animation>(ResourceId id)
	{

	}

	template<>
	inline ResourceId Resources::Import<Skeleton>(const char* file)
	{

		if (file)
		{
			/*if (GetExtension(file) == ".lnanimation")
			{

			}
			else if (CheckExtension(GetExtension(file)) != FileType::LFT_Animation)
			{
				std::string message = GetExtension(file) + " isnt an animation. Could not import";
				LN_WARN(message.c_str());
				return -1;
			}*/
		}
		ResourceId position = getResourcePosition(LRT_SKELETON, file);
		size_t size = m_Resources[LRT_SKELETON].size();

		ResourceId resourceId;

		if (position == size) {

			Skeleton* skl;
			if (file == "null")
			{
				skl = new Skeleton();
			}
			else if (GetExtension(file).c_str() == ".lnanimation")
			{
				skl = new Skeleton();
				skl->Import(file);
			}
			else
			{
				skl = new Skeleton();
				skl->Import(file);
			}

			if (file == "null")
			{
				PushResource(LRT_SKELETON, "animation", skl);
			}
			else
				PushResource(LRT_SKELETON, file, skl);

			resourceId = size;
		}
		else {
			resourceId = position;
		}
		return resourceId;
	}
	template<>
	inline void Resources::Save<Skeleton>(ResourceId id)
	{

	}
	template<>
	inline ResourceId Resources::Load<Skeleton>(ResourceId id, const char* path)
	{

	}
	template<>
	inline Skeleton* Resources::GetResourceById<Skeleton>(ResourceId id)
	{
		Lanna::Skeleton* skl = NULL;

		if (id >= 0 && id < m_Resources[LRT_SKELETON].size()) {
			skl = static_cast<Lanna::Skeleton*>(m_Resources[LRT_SKELETON][id]->resource);
		}

		return skl;
	}
	template<>
	inline std::string Resources::GetPathById<Skeleton>(ResourceId id)
	{

	}
}
#endif // !RESOURCES_H
