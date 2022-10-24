#pragma once

#include <vector>

namespace Lanna {


	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void LoadFromFile(const char* file);
		void Render();
		unsigned int GetBuffer() { return buffer; }

	private:
		void GenerateBuffers();

	public:
		unsigned int vao, ibo, buffer;				// vertex array object, intex buffer data, vertex buffer data

		std::vector<float> vao_data;
		std::vector<int> ibo_data;



		//float vao_data[9] = { 0.3f, 0.21f, 0.f,
		//						0.34f, 0.215f, 0.f,
		//						0.32f,0.25f, 0.f };
		//int ibo_data[3] = { 0,1,2 };
	};

}