#pragma once
#include "lnpch.h"

#include "Lanna/GameObject/Components/TransformComponent.h"

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
		std::vector<Bone*> bones;
		
		

	};
}


