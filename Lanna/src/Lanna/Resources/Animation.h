#pragma once
#include "lnpch.h"
#include <glm.hpp>

struct aiAnimation;
struct aiNodeAnim;

namespace Lanna {

	
	
	struct VectorKey
	{
		double time;
		glm::vec3 value;
		VectorKey(double t,float x, float y, float z) {
			value = glm::vec3(x, y, z);
			time = t;
		}
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
	};
	   
	struct AniChannel
	{
		std::string name = "Unkown";

		std::vector<VectorKey*>positionKeys;
		std::vector<VectorKey*>scaleKeys;
		std::vector<QuatKey*>rotationKeys;
		std::vector<AniChannel*> children;


		AniChannel(aiNodeAnim* channel);
		void DisplayChildren();
	};

	struct MetaAnimation
	{
		std::string name = "unknown";
		std::vector<AniChannel*> m_Channels;
		double duration;
		double tickrate;


		void Import(aiAnimation* ani);
		void DisplayBonesList();
	};

	class Animation
	{
	public:
		Animation();
		~Animation();

		void Import(const char* file);
	public:
		std::vector<MetaAnimation*> anims;
		void DisplayAnimationsList();
	};
}

