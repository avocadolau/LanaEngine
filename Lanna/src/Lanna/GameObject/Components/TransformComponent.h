#pragma once
#include "Lanna/GameObject/Component.h"

#include "vec3.hpp"

#include <glew.h>
#include <gl/GL.h>

namespace Lanna
{
	class TransformComponent : public Component
	{

	public:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		glm::vec3 w_Pos;
		glm::vec3 w_Rot;
		glm::vec3 w_Scl;
		
		TransformComponent* parent = nullptr;

		bool changed = false;
	public:
		TransformComponent();
		TransformComponent(TransformComponent* copy);
		TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		void SetPosition(glm::vec3 pos);
		void SetRotation(glm::vec3 rot);
		void SetScale(glm::vec3 scl);

		glm::vec3 GetPosition() { return m_Position; }
		glm::vec3 GetRotation() { return m_Rotation; }
		glm::vec3 GetScale() { return m_Scale; }

		/*void SetPosition(glm::vec3 position);
		void SetRotation(glm::vec3 rotation);
		void SetScale(glm::vec3 scale);*/

		void UpdateWorldTransform();

		void Use() override;
		void ImGuiDraw() override;

		~TransformComponent();


	};
}