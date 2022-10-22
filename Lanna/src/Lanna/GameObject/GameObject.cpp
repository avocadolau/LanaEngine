#include "lnpch.h"
#include "GameObject.h"
#include <vector>

#include "Component.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/CameraComponent.h"

#include "Lanna/Application.h"
#include "Lanna/EntityManager.h"

GameObject::GameObject(const char* name) :m_Name(name)
{

}
GameObject::~GameObject()
{
	m_Components.clear();
	m_Children.clear();
}


void GameObject::Update() {


}
void GameObject::Render() {}

void GameObject::AddComponent(Component::Type type)
{
	Component* comp = nullptr;
	switch (type)
	{
	case Component::Type::TOTAL:
		break;
	case Component::Type::TRANSFORM:
		comp = new TransformComponent();
		break;
	case Component::Type::MESH:
		comp = new MeshComponent();
		break;
	case Component::Type::MATERIAL:
		comp = new MaterialComponent();
		break;
	case Component::Type::CAMERA:
		comp = new CameraComponent();
		break;
	default:
		break;
	}

	if (comp!=nullptr)
		m_Components.push_back(comp);
}

void GameObject::SetParent(GameObject* parent)
{
	if (parent != nullptr)
	{
		m_Parent = parent;

	}
}

void GameObject::SetChild(GameObject* child)
{
	m_Children.push_back(child);
}

void GameObject::DelChild(GameObject*child)
{
	
}

void GameObject::DelParent()
{

}

