#pragma once

#include <list>


#include "GameObject/GameObject.h"
class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void Update();
	void Render();

	void AddGameObject(GameObject* gameObject);
	GameObject* AddEmptyGameObject();
	
	void DestroyGameObject(GameObject* gameObject);
	void SetActiveEntity(unsigned int index);
	GameObject* GetActiveEntitiy() { return activeEntitiy; }

private:
	std::vector<GameObject*> m_Entities;
	GameObject* activeEntitiy;

};

