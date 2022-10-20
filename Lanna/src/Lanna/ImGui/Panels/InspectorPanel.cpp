#include "lnpch.h"
#include "imgui.h"

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

	ImGui::Begin("Configuration", &active);
	if (activeObject)
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			//TransformComponent* t = activeObject->m_Transform;
			//char title[25];

			//if (t!=nullptr)
			//{
			//	ImGui::Text("Position");

			//	// Transform x--------------------------
			//	sprintf_s(title, 25, "x:  %f", t->m_Position.x);
			//	if (ImGui::Button(""))
			//		t->m_Position.x -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Position.x += 0.1;


			//	// Transform y--------------------------
			//	sprintf_s(title, 25, "y:  %f", t->m_Position.y);
			//	if (ImGui::Button(""))
			//		t->m_Position.y -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Position.y += 0.1;

			//	// Transform z--------------------------
			//	sprintf_s(title, 25, "z:  %f", t->m_Position.z);
			//	if (ImGui::Button(""))
			//		t->m_Position.z -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Position.z += 0.1;


			//	ImGui::Text("Rotation");

			//	// Rotation x--------------------------
			//	sprintf_s(title, 25, "x:  %f", t->m_Rotation.x);
			//	if (ImGui::Button(""))
			//		t->m_Rotation.x -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Rotation.x += 0.1;


			//	// Rotation y--------------------------
			//	sprintf_s(title, 25, "y:  %f", t->m_Rotation.y);
			//	if (ImGui::Button(""))
			//		t->m_Rotation.y -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Rotation.y += 0.1;

			//	// Rotation z--------------------------
			//	sprintf_s(title, 25, "z:  %f", t->m_Rotation.z);
			//	if (ImGui::Button(""))
			//		t->m_Rotation.z -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Rotation.z += 0.1;


			//	ImGui::Text("Scale");

			//	// Scale x--------------------------
			//	sprintf_s(title, 25, "x:  %f", t->m_Scale.x);
			//	if (ImGui::Button(""))
			//		t->m_Scale.x -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Scale.x += 0.1;


			//	// Scale y--------------------------
			//	sprintf_s(title, 25, "y:  %f", t->m_Scale.y);
			//	if (ImGui::Button(""))
			//		t->m_Scale.y -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Scale.y += 0.1;

			//	// Scale z--------------------------
			//	sprintf_s(title, 25, "z:  %f", t->m_Scale.z);
			//	if (ImGui::Button(""))
			//		t->m_Scale.z -= 0.1;
			//	ImGui::SameLine();
			//	ImGui::Text(title);
			//	ImGui::SameLine();
			//	if (ImGui::Button(""))
			//		t->m_Scale.z += 0.1;

			//}
		}
		
		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::Text("WORK IN PROGRESS");
			ImGui::Text("BUTTON TO CHANGE MESH");
		}
		if (ImGui::CollapsingHeader("Material"))
		{
			ImGui::Text("WORK IN PROGRESS");
			ImGui::Text("BUTTON TO CHANGE MATERIAL");
		}
	}

	ImGui::End();
}
