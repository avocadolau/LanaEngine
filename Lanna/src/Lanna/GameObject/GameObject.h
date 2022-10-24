#pragma once
#include "lnpch.h"
#include <vector>

#include "Component.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MaterialComponent.h"

class GameObject
{
public:

	GameObject(const char* name);
	~GameObject();


	void Update();
	void Render();

	void AddComponent(Component::Type type);

	void SetParent(GameObject* parent);
	void SetChild(GameObject* child);
	void DelChild(GameObject*child);
	void DelParent();

public:
	bool active = true;
	int mainOrder = -1;
	int secOrder = -1;

	std::list<Component*> m_Components;
	std::list<GameObject*> m_Children;
	TransformComponent* m_Transform = nullptr;
	GameObject* m_Parent = nullptr;
	const char* m_Name;
	int m_Hierarchy;
};

