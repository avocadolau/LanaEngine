#include "lnpch.h"
#include "AnimationPanel.h"

#include "imgui.h"
#include "Lanna/Application.h"
#include "Lanna/Resources/Animation.h"

namespace Lanna
{
	AnimPanel::AnimPanel(): Panel("Animation")
	{
		active = true;
	}

	AnimPanel::~AnimPanel()
	{
	}

	void AnimPanel::Draw()
	{
		ImGui::Begin(name, &active);

		if (ImGui::Button("select animation"))
		{
			if (ImGui::BeginMenu("uwu"))
			{
				
				ImGui::EndMenu();
			}
		}

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
		ImGui::BeginChild("bones", ImVec2(ImGui::GetContentRegionAvail().x * 0.2, ImGui::GetContentRegionAvail().y), false, window_flags);
		ImGui::GetScrollY();

#ifdef DEBUG_ANIM
		ani = LN_RESOURCES.GetResourceById<Animation>(0);
#endif // DEBUG_ANIM


		if (ani)
		{
			ani->DisplayAnimationsList();
		}
		ImGui::EndChild();

		// ----------------------------------------------------------------------
		ImGui::SameLine();

		ImGui::BeginChild("graphic", ImVec2(ImGui::GetContentRegionAvail().x * 0.8, ImGui::GetContentRegionAvail().y), false);
		ImGui::Text("GRAPHIC");
		ImGui::EndChild();


		ImGui::End();
	}

}