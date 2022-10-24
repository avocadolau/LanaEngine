#include "lnpch.h"
#include "EntityManager.h"

#include <vector>

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	m_Entities.clear();
}

void EntityManager::Init()
{
	GameObject* go = AddEmptyGameObject("empty");
	activeEntitiy = go;
	go->SetChild(new GameObject("uwwwwuu"));

	AddEmptyGameObject("uwu");
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
	m_Entities.push_back(gameObject);
}

GameObject* EntityManager::AddEmptyGameObject(const char* name)
{
	GameObject* object = new GameObject(name);
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

void EntityManager::SetActiveEntity(unsigned int index=-1)
{
	if (index == -1) activeEntitiy = nullptr;
	else
	{
		activeEntitiy = m_Entities.at(index);
	}


}

