#include "lnpch.h"


#include "SkeletonComponent.h"
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
	SkeletonComponent::SkeletonComponent(): Component(Component::Type::SKELETON)
	{
		name = "Skeleton Component";
	}

	SkeletonComponent::SkeletonComponent(SkeletonComponent* copy): Component(Component::Type::SKELETON)
	{
		name = "Mesh Component";
		if (copy->m_SkeletonID != -1)
		{
			m_SkeletonID = copy->m_SkeletonID;
		}
	}

	SkeletonComponent::~SkeletonComponent()
	{
	}

	void SkeletonComponent::Use()
	{
		
	}

	void SkeletonComponent::ImGuiDraw()
	{
		if (ImGui::TreeNode("Skeleton"))
		{
			if (m_SkeletonID == -1)
			{

			}
			else
			{
				static bool render = true;
				ImGui::Text("skeleton name");
				ImGui::Text("button to show hierarchy");

				ImGui::Separator();

			}

			bool reset = false;
			if (ImGui::Button("Select Skeleton"))
			{
				ImGui::OpenPopup("select skeleton");
				reset = true;
			}
			if (ImGui::BeginPopupModal("select skeleton", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				m_SkeletonID = LN_RESOURCES.SelectResourcePopUp(Resources::ResourceType::LRT_SKELETON, reset);
				//ImGui::SetItemDefaultFocus();
				//ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					m_SkeletonID = (ResourceId)-1;
				}
				ImGui::EndPopup();
			}


			ImGui::TreePop();
		}
	}

	void SkeletonComponent::Render()
	{
		// render bone boxes
	}

	bool SkeletonComponent::LoadFromFile(const char* file)
	{
		//m_SkeletonID= LN_RESOURCES.Import<Skeleton>(file);
		return false;
	}

}