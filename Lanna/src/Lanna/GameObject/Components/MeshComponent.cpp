#include "lnpch.h"


#include "MeshComponent.h"
#include "Lanna/GameObject/Component.h"

#include "Lanna/Log.h"
#include "Lanna/Application.h"
#include "Lanna/Resources.h"
#include "Lanna/Render3D.h"
#include "Lanna/Renderer/Mesh.h"

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
		Mesh* m_Mesh = LN_RESOURCES.GetResourceById<Mesh>(m_MeshID);
		m_Mesh->Render();
	}

	void MeshComponent::LoadFromFile(const char* file)
	{
		m_MeshID = LN_RESOURCES.Import<Mesh>(file);

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