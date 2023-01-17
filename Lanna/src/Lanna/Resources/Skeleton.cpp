#include "lnpch.h"
#include "Skeleton.h"


#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "imgui.h"
#include <gtx/rotate_vector.hpp>

// to delete
#include "Lanna/Resources/Mesh.h"
#include "Lanna/Application.h"
#include "Lanna/Resources.h"
#include "Lanna/EntityManager.h"
#include "Lanna/GameObject/GameObject.h"


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
					int jhjhg = bones.size();
					const char* uwu = "aslkdfja";

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


			ImGui::TreePop();
		}
		return ret;
	}

	void Skeleton::RenderBones()
	{
		for (Bone* bone : bones)
		{
			bone->RenderBone();
		}
	}

	void Skeleton::SkinMesh(ResourceId meshId)
	{
		if (meshId != 0)
		{
			Mesh* mesh = LN_RESOURCES.GetResourceById<Mesh>(meshId);
			for (Bone* b : bones)
			{
				b->v_data = &mesh->models[0]->vbo_data;
			}
		}
	}

	void Skeleton::FindBones(aiMesh** meshes, const aiNode* node, std::vector<const aiNode*>& boneNodes)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
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

	void Skeleton::ExtractBones(aiMesh* mesh, const aiNode* node, Bone* bone, aiBone* prev)
	{
		Bone* nBone = nullptr;
		for (int i = 0; i < mesh->mNumBones; i++)
		{
			if (node->mName == mesh->mBones[i]->mName)
			{
				nBone = new Bone();

				nBone->parent = bone;
				nBone->name = node->mName.C_Str();
				//if (bone) nBone->transform.parent = &bone->transform;

				for (int j = 0; j < 4; j++)
					for (int k = 0; k < 4; k++)
					{
						nBone->m_OffsetMat[j][k] = mesh->mBones[i]->mOffsetMatrix[j][k];
					}

				aiVector3D pos, rot, scl, offpos, offrot, offscl;
				node->mTransformation.Decompose(scl, rot, pos);
				mesh->mBones[i]->mOffsetMatrix.Inverse().Decompose(offscl, offrot, offpos);

				//if (bone) nBone->transform.parent = &bone->transform;
				nBone->pos =nBone->wpos = glm::vec3(offpos.x, offpos.y, offpos.z);
				nBone->rot =nBone->wrot = glm::vec3(offrot.x, offrot.y, offrot.z);
				nBone->scl =nBone->wscl = glm::vec3(offscl.x, offscl.y, offscl.z);
				//nBone->transform.SetWorldTransform(glm::vec3(offpos.x, offpos.y, offpos.z), glm::vec3(offrot.x, offrot.y, offrot.z), glm::vec3(offscl.x, offscl.y, offscl.z));


				for (int j = 0; j < mesh->mBones[i]->mNumWeights; j++)
				{
					nBone->weights.push_back(new VertexWeights(mesh->mBones[i]->mWeights[j].mVertexId, mesh->mBones[i]->mWeights[j].mWeight));
				}

				/*if (bone)
					bone->children.push_back(nBone);
				else
					bones.push_back(nBone);*/
				bones.push_back(nBone);

				break;
			}

		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			/*if (nBone)
				ExtractBones(mesh, node->mChildren[i], nBone);
			else
				ExtractBones(mesh, node->mChildren[i], bone);*/
			ExtractBones(mesh, node->mChildren[i], nullptr);
		}
	}

	void Bone::RenderBone()
	{

		//LN_RENDERER.RenderMeshColor(LN_ANIMATIONS.boneMesh, transform.w_Pos, transform.w_Rot, transform.w_Scl, m_OffsetMat, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false);
		//LN_RENDERER.RenderMeshColor(LN_ANIMATIONS.boneMesh, transform.m_Position, transform.m_Rotation,transform.m_Scale, m_OffsetMat, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false);
		//if (parent)
		//{
		//	LN_RENDERER.RenderLine(transform.w_Pos,parent->transform.w_Pos, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false);
		//	//LN_RENDERER.RenderLine(transform.m_Position, transform.parent->m_Position, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false);
		//}
		LN_RENDERER.RenderMeshColor(LN_ANIMATIONS.boneMesh, wpos, wrot, wscl, color, false);
		//LN_RENDERER.RenderMeshColor(LN_ANIMATIONS.boneMesh, transform.w_Pos, transform.w_Rot, transform.w_Scl, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false);
		/*if (children.size() == 0)
		{
			LN_RENDERER.RenderMeshColor(LN_ANIMATIONS.boneMesh, transform.m_Position, transform.m_Rotation, transform.m_Scale, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), false);
		}*/
	}

	void Bone::RenderWeights()
	{

	}


}