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
	m_Transform = new TransformComponent();
}
GameObject::~GameObject()
{
	delete m_Transform;
	m_Components.clear();
	m_Children.clear();
}


void GameObject::Update() {

	
	for (Component* c : m_Components)
	{
		if (c->m_Type == Component::Type::CAMERA)
		{
			for (Component* t : m_Components)
			{
				if (t->m_Type == Component::Type::TRANSFORM)
				{
					
				}
			}
		}
	}

}
void GameObject::Render() {}

void GameObject::AddComponent(Component::Type type)
{
	switch (type)
	{
	case Component::Type::TOTAL:
		break;
	/*case Component::Type::TRANSFORM:
		m_Transform = new TransformComponent();
		m_Components.push_back(m_Transform);
		break;*/
	case Component::Type::MESH:
		m_Components.push_back(new MeshComponent());
		break;
	case Component::Type::MATERIAL:
		m_Components.push_back(new MaterialComponent());
		break;
	case Component::Type::CAMERA:
		CameraComponent*c = new CameraComponent();
		c->AddTransformComponent(m_Transform);
		m_Components.push_back(c);
		break;
	}
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

