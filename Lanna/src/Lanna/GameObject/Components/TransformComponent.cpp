
#include "lnpch.h"
#include "TransformComponent.h"

#include "Lanna/GameObject/Component.h"

#include "vec3.hpp"

#include <gl/GL.h>
#include "imgui.h"

TransformComponent::TransformComponent() : Component(Component::Type::TRANSFORM)
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}
TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Component(Component::Type::TRANSFORM)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale = scale;
}


void TransformComponent::SetPosition(glm::vec3 position) { m_Position = position; }
void TransformComponent::SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
void TransformComponent::SetScale(glm::vec3 scale) { m_Scale = scale; }

void TransformComponent::Use()
{
}

void TransformComponent::ImGuiDraw()
{
	if (ImGui::CollapsingHeader("Transform"))
	{

		ImGui::Text("Position");
		ImGui::Text("x");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Position.x, 0.1f);
		ImGui::Text("y");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Position.y, 0.1f);
		ImGui::Text("z");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Position.z, 0.1f);

		//ImGui::DragFloat("##value", &m_Position.x, 1.0f);

		ImGui::Text("Rotation");
		ImGui::Text("x");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Rotation.x, 0.1f);
		ImGui::Text("y");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Rotation.y, 0.1f);
		ImGui::Text("z");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Rotation.z, 0.1f);


		ImGui::Text("Scale");
		ImGui::Text("x");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Scale.x, 0.1f);
		ImGui::Text("y");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Scale.y, 0.1f);
		ImGui::Text("z");
		ImGui::SameLine();
		ImGui::InputFloat("##value", &m_Scale.z, 0.1f);
		
	}


}


TransformComponent::~TransformComponent() {}