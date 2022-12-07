#pragma once
#include "lnpch.h"
#include <vector>

#include "Component.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/CameraComponent.h"


namespace Lanna
{
	class GameObject
	{
	public:
		GameObject(GameObject* copy);
		GameObject(const char* name);
		~GameObject();


		void Update();
		void Render();

		Component* AddComponent(Component::Type type);

		void AddCopyChild(GameObject* child);
		void AddEmptyChild();
		void DelChild(GameObject* child);
		void DestroyChild(GameObject* child);
		void DestroyComponent(Component* comp);
	public:
		bool active = true;

		std::vector<Component*> m_Components;
		std::vector<GameObject*> m_Children;
		TransformComponent* m_Transform = nullptr;
		MaterialComponent* m_Material = nullptr;
		MeshComponent* m_Mesh = nullptr;
		CameraComponent* m_Camera = nullptr;
		GameObject* m_Parent = nullptr;
		std::string m_Name;
		bool loockComonents = false;
		bool canDelete = true;
	};

}