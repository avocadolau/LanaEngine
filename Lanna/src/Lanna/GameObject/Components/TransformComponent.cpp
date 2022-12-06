
#include "lnpch.h"
#include "TransformComponent.h"

#include "Lanna/GameObject/Component.h"

#include "vec3.hpp"

#include <gl/GL.h>
#include "imgui.h"

namespace Lanna
{
	TransformComponent::TransformComponent() : Component(Component::Type::TRANSFORM)
	{
		m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		UpdateWorldTransform();
	}
	TransformComponent::TransformComponent(TransformComponent* copy) : Component(Component::Type::TRANSFORM)
	{
		m_Position = copy->m_Position;
		m_Rotation = copy->m_Rotation;
		m_Scale = copy->m_Scale;
		UpdateWorldTransform();
	}
	TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Component(Component::Type::TRANSFORM)
	{
		m_Position = position;
		m_Rotation = rotation;
		m_Scale = scale;
		UpdateWorldTransform();
	}


	/*void TransformComponent::SetPosition(glm::vec3 position) { m_Position = position; }
	void TransformComponent::SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
	void TransformComponent::SetScale(glm::vec3 scale) { m_Scale = scale; }*/

	void TransformComponent::UpdateWorldTransform()
	{
		if (parent)
		{
			w_Pos = parent->w_Pos + m_Position;
			w_Rot = parent->w_Rot + m_Rotation;
			w_Scl = parent->w_Scl * m_Scale;
		}
		else
		{
			w_Pos = m_Position;
			w_Rot = m_Rotation;
			w_Scl = m_Scale;
		}
	}

	void TransformComponent::Use()
	{
		if (changed)
		{
			UpdateWorldTransform();
		}
		else if (parent) {
			if (parent->changed)
				UpdateWorldTransform();
		}
	}

	void TransformComponent::ImGuiDraw()
	{
		if (ImGui::TreeNode("Transform"))
		{

			ImGui::Text("Position");
			ImGui::Text("x");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("pos  x", &m_Position.x, 0.01f))
				changed = true;
			ImGui::Text("y");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("posy y", &m_Position.y, 0.01f))
				changed = true;
			ImGui::Text("z");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("pos z", &m_Position.z, 0.01f))
				changed = true;

			ImGui::Text("Rotation");
			ImGui::Text("x");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("rot x", &m_Rotation.x, 0.001f))
				changed = true;
			ImGui::Text("y");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("rot y", &m_Rotation.y, 0.001f))
				changed = true;
			ImGui::Text("z");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("rot z", &m_Rotation.z, 0.001f))
				changed = true;


			ImGui::Text("Scale");
			ImGui::Text("x");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("scale x", &m_Scale.x, 0.01f))
				changed = true;
			ImGui::Text("y");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("scale y", &m_Scale.y, 0.01f))
				changed = true;
			ImGui::Text("z");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(-FLT_MIN);
			if (ImGui::DragFloat("scale z", &m_Scale.z, 0.01f))
				changed = true;

			ImGui::TreePop();
		}


	}


	TransformComponent::~TransformComponent() {}
}