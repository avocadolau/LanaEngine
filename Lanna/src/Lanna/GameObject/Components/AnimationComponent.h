#pragma once

#include "Lanna/GameObject/Component.h"
#include "Lanna/Resources/Framebuffer.h"
#include "Lanna/Resources.h"
#include <vector>

namespace Lanna
{
	class AnimationComponent : public Component
	{
	public:
		AnimationComponent();
		AnimationComponent(AnimationComponent* copy);
		~AnimationComponent();

		void Use() override;
		void ImGuiDraw() override;
		void Render();

		bool LoadFromFile(const char* file);
		bool Link(Skeleton* skl);
		bool IsLinked();
		//MeshComponent* loadmesh(const aiMesh* mesh);
	public:
		ResourceId m_AnimationID = -1;
		//const char* source;
	};
}