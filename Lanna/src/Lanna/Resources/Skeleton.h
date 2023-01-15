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
		std::vector<Bone*> children;
		std::vector<VertexWeights*> weights;
		TransformComponent transform;
		glm::mat4 m_OffsetMat;
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
	private:
		void FindBones(aiMesh** meshes, const aiNode* node, std::vector<const aiNode*>& boneNodes);
		void ExtractBones(aiMesh* mesh, const aiNode* node, Bone* bone, aiBone* prev = nullptr);
	public:
		std::string mName = "Unknown skeleton";
		std::vector<Bone*> bones;
		ResourceId meshId;

	};
}


