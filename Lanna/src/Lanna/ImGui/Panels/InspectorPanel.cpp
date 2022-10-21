#include "lnpch.h"
#include "imgui.h"
#include <list>

#include "InspectorPanel.h"
#include "Lanna/Application.h"

#include "Lanna/EntityManager.h"
#include "Lanna/GameObject/GameObject.h"
#include "Lanna/GameObject/Components/TransformComponent.h"
#include "Lanna/GameObject/Components/MeshComponent.h"
#include "Lanna/GameObject/Components/MaterialComponent.h"

InspectorPanel::InspectorPanel(): Panel("Inspector")
{

}

InspectorPanel::~InspectorPanel()
{

}

void InspectorPanel::Draw()
{
	GameObject* activeObject = Lanna::Application::Get().GetEntityManager()->GetActiveEntitiy();

	ImGui::Begin("Inspector", &active);
	if (activeObject!=nullptr)
	{
		for (Component* comps : activeObject->m_Components)
			comps->ImGuiDraw();

		ImGui::Separator();

		if (ImGui::Button("Add Component"))
		{
			addComp = !addComp;
		}

		if (addComp)
		{
			if (ImGui::Button("Transform"))
			{
				activeObject->AddComponent(Component::Type::TRANSFORM);
			}

			if (ImGui::Button("Mesh"))
			{
				activeObject->AddComponent(Component::Type::MESH);
			}

			if (ImGui::Button("Material"))
			{
				activeObject->AddComponent(Component::Type::MATERIAL);
			}
		}
	}

	ImGui::End();
}
