#pragma once
#include "Lanna/Resources/Resource.h"
#include "Lanna/Renderer/Framebuffer.h"

struct aiMesh;
enum Primitives {
	CUBE,
	PYRAMID,
	PLANE,

	TOTAL
};

namespace Lanna {
    class MeshAsset : public Asset
    {
    public:
		void LoadFromFile(const char* file);
		void LoadPrimitive(Primitives type);
		MeshAsset* loadmesh(const aiMesh* mesh);
    private:
		void GenrateBuffers();
    public:
		unsigned int vao = -1;				// vertex array object
		unsigned int ebo = -1;				// element buffer object
		unsigned int vbo = -1;				// vertex buffer object

		std::vector<float> vbo_data;
		std::vector<int> ebo_data;
		std::vector<MeshAsset*> models;
		Lanna::Framebuffer* buff;
		bool is_root = false;
		std::string m_ModelPath;
		const char* source;
    };
}