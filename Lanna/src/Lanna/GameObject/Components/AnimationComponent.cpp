#include "lnpch.h"


#include "AnimationComponent.h"
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
	AnimationComponent::AnimationComponent(): Component(Component::Type::ANIMATION)
	{
		name = "Animation Component";
	}

	AnimationComponent::AnimationComponent(AnimationComponent* copy): Component(Component::Type::ANIMATION)
	{
		name = "Mesh Component";
		if (copy->m_AnimationID != -1)
		{
			m_AnimationID = copy->m_AnimationID;
		}
	}

	AnimationComponent::~AnimationComponent()
	{
	}

	void AnimationComponent::Use()
	{
		
	}

	void AnimationComponent::ImGuiDraw()
	{
		if (ImGui::TreeNode("Animation"))
		{
			if (m_AnimationID == -1)
			{

			}
			else
			{
				StateMachine* ani = LN_RESOURCES.GetResourceById<StateMachine>(m_AnimationID);
				
				ImGui::Text("button to show hierarchy");

				ImGui::Separator();

			}

			bool reset = false;
			if (ImGui::Button("Select Animation"))
			{
				ImGui::OpenPopup("select Animation");
				reset = true;
			}
			if (ImGui::BeginPopupModal("select Animation", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				m_AnimationID = LN_RESOURCES.SelectResourcePopUp(Resources::ResourceType::LRT_ANIMATION, reset);
				//ImGui::SetItemDefaultFocus();
				//ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					m_AnimationID = (ResourceId)-1;
				}
				ImGui::EndPopup();
			}


			ImGui::TreePop();
		}
	}

	void AnimationComponent::Render()
	{
		// render bone boxes
	}

	bool AnimationComponent::LoadFromFile(const char* file)
	{
		//m_AnimationID= LN_RESOURCES.Import<Animation>(file);
		return false;
	}

	bool AnimationComponent::Link(Skeleton* skl)
	{
		return LN_RESOURCES.GetResourceById<StateMachine>(m_AnimationID)->LinkSkeleton(skl);
	}

	bool AnimationComponent::IsLinked()
	{
		if (m_AnimationID == -1)return false;
		return LN_RESOURCES.GetResourceById<StateMachine>(m_AnimationID)->linked;

	}

}