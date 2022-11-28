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
		MeshComponent(const char* file);
		~MeshComponent();

		void Use() override;
		void ImGuiDraw() override;
		void Render();

		void LoadFromFile(const char* file);
		void LoadPrimitive(Primitives type);
		MeshComponent* loadmesh(const aiMesh* mesh);
	private:
		void GenerateBuffers();
	public:
		unsigned int vao = -1;				// vertex array object
		unsigned int ebo = -1;				// element buffer object
		unsigned int vbo = -1;				// vertex buffer object

		std::vector<float> vbo_data;
		std::vector<int> ebo_data;
		std::vector<MeshComponent*> models;
		Lanna::Framebuffer* buff;
		bool is_root = false;
		
		ResourceId m_MeshID;
		std::string m_ModelPath;
		const char* source;
	};
}