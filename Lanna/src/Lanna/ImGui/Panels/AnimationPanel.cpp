#include "lnpch.h"
#include "AnimationPanel.h"

#include "imgui.h"
#include "Lanna/Application.h"
#include "Lanna/Resources/Animation.h"
#include "Lanna/Resources/Skeleton.h"

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

		/*if (ImGui::Button("select animation"))
		{
			if (ImGui::BeginMenu("uwu"))
			{
				
				ImGui::EndMenu();
			}
		}*/
		skl = LN_RESOURCES.GetResourceById<Skeleton>(0);
		static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | !ImGuiTableFlags_BordersOuter | !ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
		if (ImGui::BeginTable("ANIMATION", 2, flags))
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
			ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x*1,ImGui::GetContentRegionAvail().y), false, window_flags);
			if (skl)
			{
				if (ImGui::TreeNode(skl->mName.c_str()))
				{
					//bone = nullptr;
					for (Bone* b : skl->bones)
					{
						Bone* ret= skl->ImGuiHierarchyDraw(b);
						if (ret)
							bone = ret;
					}
					ImGui::TreePop();
				}
			}
			ImGui::EndChild();

			// ----------------------------------------------------------------------------
			ImGui::TableNextColumn();
			ImGui::Text("GRAPHIC");
			if (bone)
			{
				ImGui::Text(bone->name.c_str());
				ImGui::InputFloat("pos x", &bone->transform.m_Position.x);
				ImGui::InputFloat("pos y", &bone->transform.m_Position.y);
				ImGui::InputFloat("pos x", &bone->transform.m_Position.z);

				ImGui::Text("");
				ImGui::InputFloat("rot x", &bone->transform.m_Rotation.x);
				ImGui::InputFloat("rot y", &bone->transform.m_Rotation.y);
				ImGui::InputFloat("rot x", &bone->transform.m_Rotation.z);

				ImGui::Text("");
				ImGui::InputFloat("scale x", &bone->transform.m_Scale.x);
				ImGui::InputFloat("scale y", &bone->transform.m_Scale.y);
				ImGui::InputFloat("scale x", &bone->transform.m_Scale.z);

				ImGui::Text("world transform");
				ImGui::InputFloat("world pos x", &bone->transform.w_Pos.x);
				ImGui::InputFloat("world pos y", &bone->transform.w_Pos.y);
				ImGui::InputFloat("world pos x", &bone->transform.w_Pos.z);

				ImGui::Text("");
				ImGui::InputFloat("world rot x", &bone->transform.w_Rot.x);
				ImGui::InputFloat("world rot y", &bone->transform.w_Rot.y);
				ImGui::InputFloat("world rot x", &bone->transform.w_Rot.z);

				ImGui::Text("");
				ImGui::InputFloat("world scale x", &bone->transform.w_Scl.x);
				ImGui::InputFloat("world scale y", &bone->transform.w_Scl.y);
				ImGui::InputFloat("world scale x", &bone->transform.w_Scl.z);
			}


			ImGui::EndTable();
		}

		ImGui::End();
	}

	void AnimPanel::SetActiveBone(Bone* b)
	{
		bone = b;
	}

}