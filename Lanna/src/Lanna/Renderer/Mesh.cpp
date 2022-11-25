#include "lnpch.h"
#include "Mesh.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Lanna {
	Mesh::Mesh()
	{

	}

	Mesh::Mesh(const char* file)
	{
		LoadFromFile(file);
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::LoadFromFile(const char* file)
	{
		vbo_data.clear();
		ebo_data.clear();
		const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			LN_ERROR("Couldn't load mesh file: {0}", file);
		}
		LN_CORE_INFO("Loading mesh file at: {0} ...", file);
		is_root = true;

		if (scene != nullptr && scene->HasMeshes())
		{
			for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
				Mesh* model = loadmesh(scene->mMeshes[i]);

				models.push_back(model);
			}

			aiReleaseImport(scene);
		}
		else {
			LN_CORE_INFO("Error loading mesh {0} with error {1}", file, aiGetErrorString());
		}
		m_ModelPath = file;
		GenerateBuffers();
	}

	void Mesh::LoadPrimitive(Primitives primitive)
	{
		vbo_data.clear();
		ebo_data.clear();
		switch (primitive)
		{
		case CUBE:
			LoadFromFile("resources/models/Primitives/cube.fbx");
			m_ModelPath = "Cube primitive";
			break;
		case PYRAMID:
			LoadFromFile("resources/models/Primitives/pyramid.fbx");
			m_ModelPath = "Pyramid primitive";
			break;
		case PLANE:
			LoadFromFile("resources/models/Primitives/plane.fbx");
			m_ModelPath = "Plane primitive";
			break;
		}
	}

	Mesh* Mesh::loadmesh(const aiMesh* mesh)
	{
		Mesh* model = new Mesh();

		for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
			// Vertices
			model->vbo_data.push_back(mesh->mVertices[j].x);
			model->vbo_data.push_back(mesh->mVertices[j].y);
			model->vbo_data.push_back(mesh->mVertices[j].z);
			// Normals
			model->vbo_data.push_back(mesh->mNormals[j].x);
			model->vbo_data.push_back(mesh->mNormals[j].y);
			model->vbo_data.push_back(mesh->mNormals[j].z);
			// Texture coordinates
			if (mesh->mTextureCoords[0])
			{
				model->vbo_data.push_back(mesh->mTextureCoords[0][j].x);
				model->vbo_data.push_back(mesh->mTextureCoords[0][j].y);
			}
			else {
				model->vbo_data.push_back(0.0f);
				model->vbo_data.push_back(0.0f);
			}
		}
		if (model->vbo_data.empty())
		{
			LN_CORE_INFO("Error while loading mesh vertex buffer");
		}
		else
		{
			LN_CORE_INFO("Vertex buffer generated correctly");
		}
		// Indices
		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			aiFace& face = mesh->mFaces[j];
			for (unsigned int k = 0; k < face.mNumIndices; k++) {
				model->ebo_data.push_back(face.mIndices[k]);
			}
		}
		if (model->ebo_data.empty())
		{
			LN_CORE_INFO("Error while loading mesh index buffer");
		}
		else
		{
			LN_CORE_INFO("Index buffer generated correctly");
		}
		model->GenerateBuffers();

		return model;
	}

	void Mesh::GenerateBuffers()
	{
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);


		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vbo_data.size() * sizeof(float), vbo_data.data(), GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_data.size() * sizeof(int), ebo_data.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}