#pragma once

#include "Lanna/GameObject/Component.h"
#include "Lanna/Renderer/Framebuffer.h"
#include <vector>
struct aiMesh;
enum Primitives{
	CUBE,
	PYRAMID,
	PLANE,

	TOTAL
};


class MeshComponent: public Component
{
public:
	MeshComponent();
	~MeshComponent();
	MeshComponent(const char* file);

	void Use() override;
	void ImGuiDraw() override;
	void Render();

	void LoadFromFile(const char* file);
	void LoadPrimitive(Primitives type);
	MeshComponent* loadmesh(const aiMesh* mesh);
private:
	void GenerateBuffers();
public:
	unsigned int vao, ibo, buffer;				// vertex array object, intex buffer data, vertex buffer data

	std::vector<float> vao_data;
	std::vector<int> ibo_data;
	std::vector<MeshComponent*> models;
	Lanna::Framebuffer* buff;
	bool is_root = false;
	std::string m_ModelPath;
};