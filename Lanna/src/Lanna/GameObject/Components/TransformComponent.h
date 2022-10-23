#pragma once
#include "Lanna/GameObject/Component.h"

#include "vec3.hpp"

#include <glew.h>
#include <gl/GL.h>

class TransformComponent : public Component
{

public:

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
public:
	TransformComponent();
	TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);


	glm::vec3 GetPosition() { return m_Position; }
	glm::vec3 GetRotation() { return m_Rotation; }
	glm::vec3 GetScale() { return m_Scale; }

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	void Use() override;
	void ImGuiDraw() override;

	~TransformComponent();


};