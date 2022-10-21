
#include "lnpch.h"
#include "TransformComponent.h"

#include "Lanna/GameObject/Component.h"

#include "vec3.hpp"

#include <gl/GL.h>
#include "imgui.h"

TransformComponent::TransformComponent() : Component(Component::TRANSFORM)
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}
TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Component(Component::TRANSFORM)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale = scale;
}


void TransformComponent::SetPosition(glm::vec3 position) { m_Position = position; }
void TransformComponent::SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
void TransformComponent::SetScale(glm::vec3 scale) { m_Scale = scale; }

void TransformComponent::ImGuiDraw()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		char title[25];

		ImGui::Text("Position");
		//Transform x--------------------------
		sprintf_s(title, 25, "x:  %f", m_Position.x);
		if (ImGui::Button(""))
			m_Position.x -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
		m_Position.x += 0.1;

		// Transform y--------------------------
		sprintf_s(title, 25, "y:  %f", m_Position.y);
		if (ImGui::Button(""))
			m_Position.y -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Position.y += 0.1;

		// Transform z--------------------------
		sprintf_s(title, 25, "z:  %f", m_Position.z);
		if (ImGui::Button(""))
			m_Position.z -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Position.z += 0.1;


		ImGui::Text("Rotation");
		// Rotation x--------------------------
		sprintf_s(title, 25, "x:  %f", m_Rotation.x);
		if (ImGui::Button(""))
			m_Rotation.x -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Rotation.x += 0.1;
		// Rotation y--------------------------
		sprintf_s(title, 25, "y:  %f", m_Rotation.y);
		if (ImGui::Button(""))
			m_Rotation.y -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Rotation.y += 0.1;
		// Rotation z--------------------------
		sprintf_s(title, 25, "z:  %f", m_Rotation.z);
		if (ImGui::Button(""))
			m_Rotation.z -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Rotation.z += 0.1;
		
		
		ImGui::Text("Scale");
		// Scale x--------------------------
		sprintf_s(title, 25, "x:  %f", m_Scale.x);
		if (ImGui::Button(""))
			m_Scale.x -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Scale.x += 0.1;


		// Scale y--------------------------
		sprintf_s(title, 25, "y:  %f", m_Scale.y);
		if (ImGui::Button(""))
			m_Scale.y -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Scale.y += 0.1;
		// Scale z--------------------------
		sprintf_s(title, 25, "z:  %f", m_Scale.z);
		if (ImGui::Button(""))
			m_Scale.z -= 0.1;
		ImGui::SameLine();
		ImGui::Text(title);
		ImGui::SameLine();
		if (ImGui::Button(""))
			m_Scale.z += 0.1;
	}


}


TransformComponent::~TransformComponent() {}