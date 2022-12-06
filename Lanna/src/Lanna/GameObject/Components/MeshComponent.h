#pragma once

#include "Lanna/GameObject/Component.h"
#include "Lanna/Resources/Framebuffer.h"
#include "Lanna/Resources.h"
#include <vector>
struct aiMesh;
enum Primitives{
	CUBE_,
	PYRAMID_,
	PLANE_,

	TOTAL_
};

namespace Lanna
{
	class MeshComponent : public Component
	{
	public:
		MeshComponent();
		MeshComponent(MeshComponent* copy);
		MeshComponent(const char* file);
		~MeshComponent();

		void Use() override;
		void ImGuiDraw() override;
		void Render();

		void LoadFromFile(const char* file);
		void LoadPrimitive(Primitives type);
		//MeshComponent* loadmesh(const aiMesh* mesh);
	public:
		
		ResourceId m_MeshID = -1;
		//const char* source;
	};
}