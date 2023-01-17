#pragma once
#include "lnpch.h"

#include "Lanna/GameObject/Components/TransformComponent.h"
#include "glm.hpp"

struct aiScene;
struct aiMesh;
struct aiNode;
struct aiBone;
typedef size_t ResourceId;

namespace Lanna {

	struct VertexWeights {
		unsigned int vID;
		float weight;
		VertexWeights(unsigned int id, float value) { vID = id; weight = value; }
	};

	struct Bone {
		bool active;
		unsigned int id;
		Bone* parent = nullptr;
		std::string name = "Unknown bone";
		std::vector<VertexWeights*> weights;
		glm::vec3 pos = glm::vec3();
		glm::vec3 rot = glm::vec3();
		glm::vec3 scl = glm::vec3();
		glm::vec3 wpos = glm::vec3();
		glm::vec3 wrot = glm::vec3();
		glm::vec3 wscl = glm::vec3();
		//TransformComponent transform;
		glm::mat4 m_OffsetMat;
		std::vector<float>* v_data = nullptr;
		glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		Bone()
		{

		}
		~Bone()
		{

		}
		void RenderBone();
		void RenderWeights();

	};

	class Skeleton
	{
	public:
		Skeleton();
		~Skeleton();

		void Import(const char* file);
		Bone* ImGuiHierarchyDraw(Bone* bone);
		void RenderBones();
		void SkinMesh(ResourceId meshId);
	private:
		void FindBones(aiMesh** meshes, const aiNode* node, std::vector<const aiNode*>& boneNodes);
		void ExtractBones(aiMesh* mesh, const aiNode* node, Bone* bone, aiBone* prev = nullptr);
	public:
		std::string mName = "Unknown skeleton";
		std::vector<Bone*> bones;
		ResourceId meshId;
		bool skinned = false;
	};
}


