#include "lnpch.h"


#include "MeshComponent.h"
#include "Lanna/GameObject/Component.h"

#include "Lanna/Log.h"
#include "Lanna/Application.h"
#include "Lanna/Resources.h"
#include "Lanna/Render3D.h"
#include "Lanna/Resources/Mesh.h"

#include <glew.h>
#include <glm.hpp>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <imgui.h>

namespace Lanna
{
	MeshComponent::MeshComponent() : Component(Component::Type::MESH)
	{
		name = "Mesh Component";
	}

	MeshComponent::MeshComponent(MeshComponent* copy) : Component(Component::Type::MESH)
	{
		name = "Mesh Component";

		if (copy->m_MeshID != -1)
		{
			LoadFromFile(LN_RESOURCES.GetPathById<Mesh>(copy->m_MeshID).c_str());
		}
	}

	MeshComponent::~MeshComponent()
	{

	}

	MeshComponent::MeshComponent(const char* file) : Component(Component::Type::MESH)
	{
		name = "Mesh Component";

		LoadFromFile(file);
	}

	void MeshComponent::Use()
	{
		/*int a = LN_RESOURCES.GetResourceById<Mesh>(m_MeshID)->vbo_data.size();
		std::stringstream ss;
		ss << a;
		std::string str = ss.str();
		LN_INFO(str.c_str());*/
	}

	void MeshComponent::ImGuiDraw()
	{
		if (ImGui::TreeNode("Mesh"))
		{
			if (m_MeshID == -1)
			{
				
			}

			else
			{
				std::string path = LN_RESOURCES.GetPathById<Mesh>(m_MeshID);
				if (path != "null")
				{
					ImGui::Text("Source mesh");
					ImGui::TextWrapped(LN_RESOURCES.GetPathById<Mesh>(m_MeshID).c_str());

				}
				/*if (ImGui::SmallButton("save"))
				{
					LN_RESOURCES.Save<Mesh>(m_MeshID);
				}
				ImGui::SameLine();
				if (ImGui::SmallButton("load"))
				{
					LN_RESOURCES.Load<Mesh>(m_MeshID, "TEST");

				}*/
				ImGui::SameLine();
				if (ImGui::SmallButton("Delete"))
				{
					toDel = true;
				}
				
			}

			bool reset = false;
			if (ImGui::Button("Select Resource"))
			{
				ImGui::OpenPopup("select resource");
				reset = true;
			}
			if (ImGui::BeginPopupModal("select resource", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				m_MeshID = LN_RESOURCES.SelectResourcePopUp(Resources::ResourceType::LRT_MESH, reset);
				//ImGui::SetItemDefaultFocus();
				//ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					m_MeshID = (ResourceId)-1;
				}
				ImGui::EndPopup();
			}

			static int selectedMesh = -1;
			const char* names[] = { "cube", "pyramid", "plane" };

			if (ImGui::Button("Primitives"))
				ImGui::OpenPopup("my_select_popup");


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
			
			ImGui::TreePop();
		}

		
	}

	void MeshComponent::Render()
	{
		Mesh* m_Mesh = LN_RESOURCES.GetResourceById<Mesh>(m_MeshID);
		m_Mesh->Render();
	}

	void MeshComponent::LoadFromFile(const char* file)
	{
		m_MeshID = LN_RESOURCES.Import<Mesh>(file);
		LN_RESOURCES.Save<Mesh>(m_MeshID);

	}

	void MeshComponent::LoadPrimitive(Primitives type)
	{
		const char* path;
		switch (type)
		{
		case CUBE_:
			path="resources/models/Primitives/cube.fbx";
			break;
		case PYRAMID_:
			path="resources/models/Primitives/pyramid.fbx";
			break;
		case PLANE_:
			path="resources/models/Primitives/plane.fbx";
			break;
		}
		m_MeshID = LN_RESOURCES.Import<Mesh>(path);
	}

}