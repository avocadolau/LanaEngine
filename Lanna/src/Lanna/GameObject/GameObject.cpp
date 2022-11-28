#include "lnpch.h"
#include "GameObject.h"
#include <vector>

#include "Lanna/Log.h"
#include "Component.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/CameraComponent.h"

#include "Lanna/Application.h"
#include "Lanna/EntityManager.h"

#include <glew.h>
#include <glm.hpp>


namespace Lanna
{
	GameObject::GameObject(const char* name) :m_Name(name)
	{
		AddComponent(Component::Type::TRANSFORM);
		std::string text = "";
		text= "Game object '" + (std::string)name + "' created";
		LN_TRACE(text.c_str());
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
			c->Use();
		}

	}
	void GameObject::Render() {
		if (m_Mesh)
			LN_RENDERER.RenderMesh(m_Mesh, m_Transform->m_Position, m_Transform->m_Rotation, m_Transform->m_Scale, m_Material->getMaterial(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	Component* GameObject::AddComponent(Component::Type type)
	{
		switch (type)
		{
		case Component::Type::TOTAL:
			break;
		case Component::Type::TRANSFORM:
			if (m_Transform == nullptr)
			{
				m_Transform = new TransformComponent();
				m_Components.push_back(m_Transform);
				return m_Transform;
			}
			else
			{
				LN_INFO("Already has transform component");
			}
			break;
		case Component::Type::MESH:
			if (m_Mesh == nullptr)
			{
				m_Mesh = new MeshComponent();
				m_Components.push_back(m_Mesh);
				return m_Mesh;
			}
			else
			{
				LN_INFO("Already has mesh component");
			}
			break;
		case Component::Type::MATERIAL:
			if (m_Material == nullptr)
			{
				m_Material = new MaterialComponent();
				m_Components.push_back(m_Material);
				return m_Material;
			}
			else
			{
				LN_INFO("Already has material component");
			}
			break;
		case Component::Type::CAMERA:
			if (m_Camera == nullptr)
			{
				if (m_Transform == nullptr) AddComponent(Component::Type::TRANSFORM);
				//m_Camera = new CameraComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), YAW, PITCH);
				m_Camera = new CameraComponent(m_Transform);
				m_Components.push_back(m_Camera);
				loockComonents = true;
				return m_Camera;
			}
			else
			{
				LN_INFO("Already has camera component");
			}
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

	void GameObject::DelChild(GameObject* child)
	{

	}

	void GameObject::DelParent()
	{

	}

}