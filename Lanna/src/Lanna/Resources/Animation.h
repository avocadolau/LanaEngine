#pragma once
#include "lnpch.h"
#include <glm.hpp>
#include "Skeleton.h"

struct aiAnimation;
struct aiNodeAnim;
struct aiNode;

namespace Lanna {

	
	
	struct VectorKey
	{
		double time;
		glm::vec3 value;
		VectorKey(double t,float x, float y, float z) {
			value = glm::vec3(x, y, z);
			time = t;
		}
		VectorKey();
	};
	struct QuatKey
	{
		double time;
		glm::vec4 value;
		QuatKey(double t, float q0,float q1, float q2, float q3)
		{
			value = glm::vec4(q0, q1, q2, q3);
			time = t;
		}
		QuatKey();
	};
	   
	struct AniChannel
	{
		std::string name = "Unkown";

		std::vector<VectorKey*>positionKeys;
		std::vector<VectorKey*>scaleKeys;
		std::vector<QuatKey*>rotationKeys;
		std::vector<AniChannel*> children;
		glm::mat4 pTransformations;
		glm::vec3 pRot;
		glm::vec3 pScl;
		Bone* m_Bone=nullptr;

		AniChannel(aiNodeAnim* channel);
		void MoveBone(glm::mat4 translations, glm::vec3 totalRotations, glm::vec3 totalScales, unsigned int frame);
		void FollowParent(glm::mat4 offsetmat, glm::vec3 translate, glm::vec4 rotate, glm::vec3 scale);
		void GetKeys(glm::vec3*pos, glm::vec3*scale, glm::vec4*rot, unsigned int frame);
		void SetFromKeys(glm::mat4 prevView, glm::vec3 prevRot, unsigned int frame);
		void SetFromKeys(glm::mat4 transformation, glm::mat4 prevoffsetmat, unsigned int frame);
		void FollowParent(AniChannel* parent, glm::mat4 translations);
		void Reset();
		
	};

	struct Animation
	{
		unsigned int offset = 0;
		unsigned int currFrame = 0;
		unsigned int lastFrame = 0;
		std::string name = "unknown";
		std::vector<AniChannel*> m_Channels;
		std::vector<glm::mat4> localTranslation;
		double duration;
		double tickrate;

		AniChannel* ImGuiHierarchyDraw(AniChannel* channel= nullptr);
		void Import(aiAnimation* ani, aiNode* node, AniChannel* channel);
		void LinkBone(AniChannel* channel,Skeleton*skl);
		void Update();
		void MoveBones();
		
	};

	class StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		void Import(const char* file);
		bool LinkSkeleton(Skeleton* skl);
		void Update();
	public:
		std::vector<Animation*> anims;
		bool linked = false;
	};
}

