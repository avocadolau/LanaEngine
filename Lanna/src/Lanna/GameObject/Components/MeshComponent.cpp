#include "lnpch.h"


#include "MeshComponent.h"
#include "Lanna/GameObject/Component.h"

#include "Lanna/Log.h"
#include "Lanna/Application.h"
#include "Lanna/Render3D.h"

#include <glew.h>
#include <glm.hpp>

#ifndef ASSIMP_NOT_WORKING
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif // !ASSIMP_NOT_WORKING



#include <imgui.h>


MeshComponent::MeshComponent() : Component(Component::Type::MESH)
{
	LoadPrimitive(Primitives::CUBE);
}
MeshComponent::~MeshComponent()
{

}

MeshComponent::MeshComponent(const char* file) : Component(Component::Type::MESH)
{
	LoadFromFile(file);
}

void MeshComponent::Use()
{

}

void MeshComponent::ImGuiDraw()
{
	if (ImGui::TreeNode("Mesh"))
	{
		static int selectedMesh = -1;
		const char* names[] = { "cube", "pyramid", "plane"};

		if (ImGui::Button("Primitives"))
			ImGui::OpenPopup("my_select_popup");
		ImGui::SameLine();
		//ImGui::TextUnformatted(selectedMesh == -1 ? "<None>" : names[selectedMesh]);
		if (ImGui::BeginPopup("my_select_popup"))
		{
			ImGui::Text("Primitives");
			ImGui::Separator();
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
				if (ImGui::Selectable(names[i]))
				{
					selectedMesh = i;
					LoadPrimitive((Primitives)i);
				} 
			if (ImGui::Selectable("<None>"))
				selectedMesh = -1;
			ImGui::EndPopup();
		}
		ImGui::Text("");
		static char buf[100] = "";
		ImGui::Text("Mesh Path");
		ImGui::SetNextItemWidth(-FLT_MIN-50);
		ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
		ImGui::SameLine();
		if (ImGui::SmallButton("load"))
		{
			LoadFromFile(buf);
		}
		ImGui::TreePop();
	}

}

void MeshComponent::Render()
{
	if (is_root) {
		size_t meshCount = models.size();

		for (size_t i = 0; i < meshCount; i++) {
			models[i]->Render();
		}
	}
	else {
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, (GLsizei)ibo_data.size(), GL_UNSIGNED_INT, 0);
	}
}

void MeshComponent::LoadFromFile(const char* file)
{
	const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		LN_ERROR("Couldn't load mesh file: {0}", file);
	}
	LN_CORE_INFO("Loading mesh file at: {0} ...", file);
	is_root = true;

	if (scene != nullptr && scene->HasMeshes())
	{
		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			MeshComponent* model = loadmesh(scene->mMeshes[i]);

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

void MeshComponent::LoadPrimitive(Primitives type)
{

	vao_data.clear();
	ibo_data.clear();

	switch (type)
	{
	case CUBE:
		vao_data=
		{
			-0.5f,-0.5f,0.5f,
			0.5f,-0.5f,0.5f,
			0.5f,0.5f,0.5f,
			-0.5f,0.5f,0.5f,

			-0.5f,-0.5f,-0.5f,
			0.5f,-0.5f,-0.5f,
			0.5f,0.5f,-0.5f,
			-0.5f,0.5f,-0.5f

		};

		ibo_data=
		{
			0,1,2,		2,3,0,
			5,4,6,		6,4,7,
			4,5,1,		1,0,4,
			5,6,2,		2,1,5,
			6,7,3,		3,2,6,
			7,4,0,		0,3,7
		};

		break;
	case PYRAMID:
		vao_data =
		{
			-0.5f,-0.5f,0.0f,
			0.5f,-0.5f,0.0f,
			0.5f,0.5f,0.0f,
			-0.5f,0.5f,0.0f,
			0.0f,0.0f,1.0f
		};

		ibo_data =
		{
			0,3,2,		2,1,0,
			0,1,4,
			1,2,4,
			2,3,4,
			3,0,4
		};

		break;
	case PLANE:

		vao_data =
		{
			-10.0f,-10.0f,0.0f,
			10.0f,-10.0f,0.0f,
			10.0f,10.0f,0.0f,
			-10.0f,10.0f,0.0f,
		};

		ibo_data =
		{
			0,1,2,		2,3,0
		};


		break;
	}
	GenerateBuffers();

}

MeshComponent* MeshComponent::loadmesh(const aiMesh* mesh)
{
	MeshComponent* model = new MeshComponent();

	for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
		// Vertices
		model->vao_data.push_back(mesh->mVertices[j].x);
		model->vao_data.push_back(mesh->mVertices[j].y);
		model->vao_data.push_back(mesh->mVertices[j].z);
		// Normals
		model->vao_data.push_back(mesh->mNormals[j].x);
		model->vao_data.push_back(mesh->mNormals[j].y);
		model->vao_data.push_back(mesh->mNormals[j].z);
		// Texture coordinates
		if (mesh->mTextureCoords[0])
		{
			model->vao_data.push_back(mesh->mTextureCoords[0][j].x);
			model->vao_data.push_back(mesh->mTextureCoords[0][j].y);
		}
		else {
			model->vao_data.push_back(0.0f);
			model->vao_data.push_back(0.0f);
		}
	}
	if (model->vao_data.empty())
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
			model->ibo_data.push_back(face.mIndices[k]);
		}
	}
	if (model->ibo_data.empty())
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

void MeshComponent::GenerateBuffers()
{
	glGenBuffers(1, &vao);
	glGenBuffers(1, &ibo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);


	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, vao_data.size() * sizeof(float), vao_data.data(), GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo_data.size() * sizeof(int), ibo_data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
