#pragma once

#include "Lanna/GameObject/Component.h"
#include "Lanna/Resources/Framebuffer.h"
#include "Lanna/Resources.h"
#include <vector>

namespace Lanna
{
	class SkeletonComponent : public Component
	{
	public:
		SkeletonComponent();
		SkeletonComponent(SkeletonComponent* copy);
		~SkeletonComponent();

		void Use() override;
		void ImGuiDraw() override;
		void Render();

		bool LoadFromFile(const char* file);
		bool IsSkinned();
		void Skin(ResourceId meshID);
		//MeshComponent* loadmesh(const aiMesh* mesh);
	public:
		
		ResourceId m_SkeletonID = -1;
		//const char* source;
	};
}