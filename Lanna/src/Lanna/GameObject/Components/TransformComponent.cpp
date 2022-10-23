
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
	if (ImGui::TreeNode("Transform"))
	{

		ImGui::Text("Position");
		ImGui::Text("x");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("pos  x", &m_Position.x, 0.1f);
		ImGui::Text("y");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("posy y", &m_Position.y, 0.1f);
		ImGui::Text("z");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("pos z", &m_Position.z, 0.1f);

		//ImGui::DragFloat("##value", &m_Position.x, 1.0f);

		ImGui::Text("Rotation");
		ImGui::Text("x");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("rot x", &m_Rotation.x, 0.1f);
		ImGui::Text("y");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("rot y", &m_Rotation.y, 0.1f);
		ImGui::Text("z");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("rot z", &m_Rotation.z, 0.1f);


		ImGui::Text("Scale");
		ImGui::Text("x");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("scale x", &m_Scale.x, 0.1f);
		ImGui::Text("y");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("scale y", &m_Scale.y, 0.1f);
		ImGui::Text("z");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputFloat("scale z", &m_Scale.z, 0.1f);
		
		ImGui::TreePop();
	}


}


TransformComponent::~TransformComponent() {}