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
	source = "no mesh";
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
		

		if (source != "no mesh")
		{
			ImGui::Text("Source mesh");
			ImGui::TextWrapped(source);
		}
		else
		{
			static int selectedMesh = -1;
			const char* names[] = { "cube", "pyramid", "plane" };

			if (ImGui::Button("Primitives"))
				ImGui::OpenPopup("my_select_popup");
			ImGui::SameLine();

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
		}
		//ImGui::TextUnformatted(selectedMesh == -1 ? "<None>" : names[selectedMesh]);
		
		/*ImGui::Text("");
		static char buf[100] = "";
		ImGui::Text("Mesh Path");
		ImGui::SetNextItemWidth(-FLT_MIN-50);
		ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
		ImGui::SameLine();
		if (ImGui::SmallButton("load"))
		{
			LoadFromFile(buf);
		}*/
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
		glDrawElements(GL_TRIANGLES, (GLsizei)ebo_data.size(), GL_UNSIGNED_INT, 0);
	}
}

void MeshComponent::LoadFromFile(const char* file)
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
			MeshComponent* model = loadmesh(scene->mMeshes[i]);

			models.push_back(model);
		}

		aiReleaseImport(scene);
		source = file;
	}
	else {
		LN_CORE_INFO("Error loading mesh {0} with error {1}", file, aiGetErrorString());
	}
	m_ModelPath = file;
	GenerateBuffers();
}

void MeshComponent::LoadPrimitive(Primitives type)
{
	vbo_data.clear();
	ebo_data.clear();
	switch (type)
	{
	case CUBE:
		LoadFromFile("resources/models/Primitives/cube.fbx");
		source = "Cube primitive";
		break;
	case PYRAMID:
		LoadFromFile("resources/models/Primitives/pyramid.fbx");
		source = "Pyramid primitive";
		break;
	case PLANE:
		LoadFromFile("resources/models/Primitives/plane.fbx");
		source = "Plane primitive";
		break;
	}
}

MeshComponent* MeshComponent::loadmesh(const aiMesh* mesh)
{
	MeshComponent* model = new MeshComponent();

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

void MeshComponent::GenerateBuffers()
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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
