#include "lnpch.h"
#include "Mesh.h"

#include "Lanna/Log.h"

#include <glm.hpp>
#include "glad/glad.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Lanna {

	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::LoadFromFile(const char* file)
	{
		const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality);
		if (scene != nullptr && scene->HasMeshes())
		{
			
			aiReleaseImport(scene);

			GenerateBuffers();
		}
		else {
			LN_CORE_ERROR("Error loading mesh {0}", file);
		}
	}

	void Mesh::Render()
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, ibo_data.size(), GL_UNSIGNED_INT, 0);
	}

	void Mesh::GenerateBuffers()
	{
		glGenBuffers(1, &buffer);		// buffer

		glGenVertexArrays(1, &vao);		// vertex array buffer
		glBindVertexArray(vao);

		// bind vertex
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, vao_data.size() * sizeof(float), vao_data.data(), GL_STATIC_DRAW);

		// bind indices
		glGenBuffers(1, &ibo);			// index buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo_data.size() * sizeof(int), ibo_data.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}