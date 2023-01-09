#include "lnpch.h"
#include "Skeleton.h"


#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "imgui.h"

namespace Lanna {
	Skeleton::Skeleton()
	{
	}
	Skeleton::~Skeleton()
	{
	}

	void Skeleton::Import(const char* file)
	{
		//const aiScene* scene = aiImportFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);
		const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_Fast);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			LN_ERROR("Couldn't load skeleton file: {0}", file);
		}
		LN_CORE_INFO("Loading skeleton file at: {0} ...", file);

		if (scene != nullptr)
		{
			if (scene->HasAnimations())
			{
				for (size_t i = 0; i < scene->mNumAnimations; i++)
				{
					// finding bones
					std::vector<const aiNode*> boneNodes;
					FindBones(scene->mMeshes, scene->mRootNode, boneNodes);

					//extracting bones
					for (int i = 0; i < boneNodes.size(); i++)
					{
						mName = boneNodes[i]->mName.C_Str();
						for (int j = 0; j < boneNodes[i]->mNumMeshes; j++)
						{
							aiMesh* bMesh = scene->mMeshes[boneNodes[i]->mMeshes[j]];
							ExtractBones(bMesh, scene->mRootNode, nullptr);
						}
					}

					// next step
				}
			}
			else LN_CORE_INFO("Couldn't find the animation at: {0}", file);
			aiReleaseImport(scene);
		}
		else {
			LN_CORE_INFO("Error loading mesh {0} with error {1}", file, aiGetErrorString());
		}
	}

	Bone* Skeleton::ImGuiHierarchyDraw(Bone* bone)
	{
		Bone* ret = nullptr;
		if (ImGui::TreeNode(bone->name.c_str()))
		{
			if (ImGui::IsItemToggledOpen())
			{
				ret = bone;
			}
			
			for (Bone* b : bone->children)
			{
				Bone* nRet= ImGuiHierarchyDraw(b);
				if (nRet) ret = nRet;
			}
			
			ImGui::TreePop();
		}
		return ret;
	}

	void Skeleton::FindBones(aiMesh** meshes, const aiNode* node, std::vector<const aiNode*>& boneNodes)
	{
		for (int i = 0; i<node->mNumMeshes; i++)
		{
			size_t meshID = node->mMeshes[i];
			if (meshes[meshID]->HasBones())
				boneNodes.push_back(node);
		}
		for (int i = 0; i < node->mNumChildren; i++)
		{
			FindBones(meshes, node->mChildren[i], boneNodes);
		}
	}

	void Skeleton::ExtractBones(aiMesh* mesh, const aiNode* node, Bone* bone)
	{
		Bone* nBone = nullptr;
		for (int i = 0; i < mesh->mNumBones; i++)
		{
			if (node->mName == mesh->mBones[i]->mName)
			{
				nBone = new Bone();
				
				nBone->name = node->mName.C_Str();
				aiVector3D pos, rot, scl;
				node->mTransformation.Decompose(scl, rot, pos);
				nBone->transform.SetPosition(glm::vec3(pos.x, pos.y, pos.z));
				nBone->transform.SetRotation(glm::vec3(rot.x, rot.y, rot.z));
				nBone->transform.SetScale(glm::vec3(scl.x, scl.y, scl.z));

				if (bone)
					bone->children.push_back(nBone);
				else
					bones.push_back(nBone);

				break;
			}
		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			if (nBone)
				ExtractBones(mesh, node->mChildren[i], nBone);
			else
				ExtractBones(mesh, node->mChildren[i], bone);
		}
	}

}