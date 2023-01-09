#pragma once
#include "lnpch.h"

#include "Lanna/GameObject/Components/TransformComponent.h"




struct aiScene;
struct aiMesh;
struct aiNode;

namespace Lanna {

	struct Bone {
		bool active;
		unsigned int id;
		Bone* parent = nullptr;
		std::string name = "Unknown bone";
		std::vector<Bone*> children;
		TransformComponent transform;


		Bone()
		{
			
		}
		~Bone()
		{

		}
		
	};

	class Skeleton
	{
	public:
		Skeleton();
		~Skeleton();

		void Import(const char* file);
		Bone* ImGuiHierarchyDraw(Bone* bone);
	private:
		void FindBones(aiMesh** meshes, const aiNode* node, std::vector<const aiNode*>& boneNodes);
		void ExtractBones(aiMesh* mesh, const aiNode* node, Bone* bone);
	public:
		std::string mName = "Unknown skeleton";
		std::vector<Bone*> bones;
		
		
		

	};
}


