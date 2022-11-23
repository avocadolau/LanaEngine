#include "lnpch.h"
#include "EntityManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/Components/TransformComponent.h"
#include "GameObject/Components/MeshComponent.h"
#include <vector>

namespace Lanna {

	EntityManager::EntityManager()
	{

	}

	EntityManager::~EntityManager()
	{
		m_Entities.clear();
	}

	void EntityManager::Init()
	{
		s_Instance = this;
		AddEmptyGameObject("uwu");
		GameObject* house = AddEmptyGameObject("House");
		MeshComponent* houseMesh = new MeshComponent("resources/models/BakerHouse.fbx");
		MaterialComponent* houseMat = new MaterialComponent("resources/images/bakerHouse.png");
		house->m_Transform->m_Position = glm::vec3(0.0, 0.0, 1.0f);
		house->m_Mesh = houseMesh;
		house->m_Material = houseMat;
		house->m_Components.push_back(houseMesh);
		house->m_Components.push_back(houseMat);

	}

	void EntityManager::Update()
	{
		for (GameObject* object : m_Entities)
			if (object->active) object->Update();
	}

	void EntityManager::Render()
	{
		for (GameObject* object : m_Entities)
			if (object->active) object->Render();
	}

	void EntityManager::AddGameObject(GameObject* gameObject)
	{
		if (gameObject)
			m_Entities.push_back(gameObject);
	}

	GameObject* EntityManager::AddEmptyGameObject(const char* name)
	{
		std::string nName = name;
		int count = 0;
		for (GameObject* object : m_Entities)
		{
			std::string nObj = object->m_Name;
			if (nObj.find(name) != -1)
				count++;
		}
		GameObject* object;
		if (count > 0)
		{
			nName.append(" ");
			nName.append(std::to_string(count + 1).c_str());
			object = new GameObject(nName.c_str());

		}
		else
			object = new GameObject(name);

		m_Entities.push_back(object);
		return object;
	}

	void EntityManager::DestroyGameObject(GameObject* gameObject)
	{
		auto it = std::find(m_Entities.begin(), m_Entities.end(), gameObject);
		if (it != m_Entities.end())
		{
			m_Entities.erase(it); //Layer isnt deleted, just removed from the actual vector
			delete gameObject;
			gameObject = nullptr;
		}
	}

	void EntityManager::SetActiveEntity(unsigned int index = -1)
	{
		if (index == -1) activeEntitiy = nullptr;
		else
		{
			activeEntitiy = m_Entities.at(index);
		}
	}

}