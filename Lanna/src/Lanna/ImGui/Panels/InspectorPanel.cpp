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
#include "Lanna/GameObject/Components/CameraComponent.h"

InspectorPanel::InspectorPanel(): Panel("Inspector")
{

}

InspectorPanel::~InspectorPanel()
{

}


void InspectorPanel::ShowObjectHierarchy(GameObject* obj)
{
	bool node_open = ImGui::TreeNode(obj->m_Name.c_str());
	ImGui::SameLine();
	if (ImGui::SmallButton("Del"))
		obj->DelParent();

	if (node_open)
	{
		for (GameObject* o : obj->m_Children)
		{
			ShowObjectHierarchy(o);
		}
		ImGui::TreePop();
	}
}

void InspectorPanel::Draw()
{
	GameObject* activeObject = Lanna::Application::Get().GetEntityManager()->GetActiveEntitiy();

	ImGui::Begin("Inspector", &active);
	if (activeObject!=nullptr)
	{
		ImGui::Text(activeObject->m_Name.c_str());

		ImGui::Text("Parent: ");
		ImGui::SameLine();
		if (activeObject->m_Parent == nullptr) ImGui::Text("None");
		else ImGui::Text(activeObject->m_Parent->m_Name.c_str());
		ImGui::SameLine();
		if (ImGui::SmallButton("Del")) {}
		if (ImGui::SmallButton("Add")){}

		/*ImGui::Text("Children");
		if(activeObject->m_Children.size()>0)
			ShowObjectHierarchy(activeObject);*/


		/*bool node_open = ImGui::TreeNode("Children");
		if (node_open)
		{
			for (GameObject* o : activeObject->m_Children)
			{
				ShowObjectHierarchy(o);
			}
			ImGui::TreePop();
		}
		if (ImGui::SmallButton("Add")) {}*/


		// components
		ImGui::Separator();
		/*activeObject->m_Transform->ImGuiDraw();*/
		for (Component* comps : activeObject->m_Components)
			comps->ImGuiDraw();
		
		ImGui::Separator();
		if (ImGui::Button("Add Component"))
			addComp = !addComp;

		if (addComp)
		{
			if (ImGui::Button("Transform"))
			{
				activeObject->AddComponent(Component::Type::TRANSFORM);
				addComp = false;
			}
			if (ImGui::Button("Mesh"))
			{
				activeObject->AddComponent(Component::Type::MESH);
				addComp = false;
			}
			if (ImGui::Button("Material"))
			{
				activeObject->AddComponent(Component::Type::MATERIAL);
				addComp = false;
			}
			if (ImGui::Button("Camera"))
			{
				activeObject->AddComponent(Component::Type::CAMERA);
				addComp = false;
			}
		}
	}

	ImGui::End();
}
