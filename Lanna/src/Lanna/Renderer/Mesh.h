#pragma once
#include "Lanna/Renderer/Framebuffer.h"
//#include "Lanna/Renderer/Material.h"

enum PrimitivesMesh {
	CUBE,
	PYRAMID,
	PLANE,

	TOTAL
};

struct aiMesh;

namespace Lanna {

	class Mesh
	{
	public:
		Mesh();
		Mesh(const char* file);
		~Mesh();

		void LoadFromFile(const char* file);
		void LoadPrimitive(PrimitivesMesh primitive);
		void Render();
		Mesh* loadmesh(const aiMesh* mesh);
	private:
		void GenerateBuffers();
	public:
		unsigned int vao = -1;				// vertex array object
		unsigned int ebo = -1;				// element buffer object
		unsigned int vbo = -1;				// vertex buffer object

		std::vector<float> vbo_data;
		std::vector<int> ebo_data;
		std::vector<Mesh*> models;
		Lanna::Framebuffer* buff;
		bool is_root = false;
	};

}