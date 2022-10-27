#include "lnpch.h"
#include "MeshComponent.h"
#include "Lanna/GameObject/Component.h"

#include "Lanna/Log.h"

#include <glew.h>
#include <glm.hpp>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <imgui.h>
MeshComponent::MeshComponent() : Component(Component::Type::MESH)
{
	LoadPrimitive(Primitives::CUBE);
}
MeshComponent::~MeshComponent()
{

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
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, ibo_data.size(), GL_UNSIGNED_INT, 0);
}

void MeshComponent::LoadFromFile(const char* file)
{
	vao_data.clear();
	ibo_data.clear();


	/*vao_data.push_back(0.3f);
	vao_data.push_back(0.21f);
	vao_data.push_back(0.0f);
	vao_data.push_back(0.34f);
	vao_data.push_back(0.21f);
	vao_data.push_back(0.0f);
	vao_data.push_back(0.32f);
	vao_data.push_back(0.25f);
	vao_data.push_back(0.0f);

	ibo_data.push_back(0);
	ibo_data.push_back(1);
	ibo_data.push_back(2);*/

	/*float vao_data[9] = { 0.3f, 0.21f, 0.f,
							0.34f, 0.215f, 0.f,
							0.32f,0.25f, 0.f };
	int ibo_data[3] = { 0,1,2 };*/



	const aiScene* scene = aiImportFile(file, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{

		aiReleaseImport(scene);

		GenerateBuffers();
	}
	else {
		LN_CORE_ERROR("Error loading mesh {0}", file);
	}

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

void MeshComponent::GenerateBuffers()
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
