#include "lnpch.h"
#include "HierarchyPanel.h"
#include <list>

#include "Lanna/Application.h"
#include "Lanna/EntityManager.h"
#include "Lanna/GameObject/GameObject.h"

HierarchyPanel::HierarchyPanel(): Panel("SceneObjects")
{

}

HierarchyPanel::~HierarchyPanel()
{

}

void HierarchyPanel::Draw()
{
	std::vector<GameObject*>* entities = Lanna::Application::Get().GetEntityManager()->GetEntityList();

	ImGui::Begin("Game Object Hierarchy", &active);

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 0.0, 0.0, 0.0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0, 0.0, 0.0, 0.0));


	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::End();	
}
