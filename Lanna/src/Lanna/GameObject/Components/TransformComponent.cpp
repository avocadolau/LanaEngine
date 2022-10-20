
#include "lnpch.h"
#include "TransformComponent.h"

#include "Lanna/GameObject/Component.h"

#include "vec3.hpp"

#include <gl/GL.h>

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


TransformComponent::~TransformComponent() {}