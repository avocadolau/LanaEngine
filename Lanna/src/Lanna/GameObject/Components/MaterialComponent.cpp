#include "lnpch.h"
#include "MaterialComponent.h"
#include "Lanna/GameObject/Component.h"

#include <imgui.h>

MaterialComponent::MaterialComponent() : Component(Component::Type::MATERIAL)
{

}
MaterialComponent::~MaterialComponent()
{

}

void MaterialComponent::Use()
{
}

void MaterialComponent::ImGuiDraw()
{

	if (ImGui::TreeNode("Material"))
	{
		static int selectedMat = -1;
		const char* names[] = { "material 1", "material 2", "material 3", "material 4", "material 5" };

		if (ImGui::Button("Select.."))
			ImGui::OpenPopup("my_select_popup");
		ImGui::SameLine();
		ImGui::TextUnformatted(selectedMat == -1 ? "<None>" : names[selectedMat]);
		if (ImGui::BeginPopup("my_select_popup"))
		{
			ImGui::Text("Assets");
			ImGui::Separator();
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
				if (ImGui::Selectable(names[i]))
					selectedMat = i;
			if (ImGui::Selectable("<None>"))
				selectedMat = -1;
			ImGui::EndPopup();
		}


		ImGui::TreePop();
	}

}