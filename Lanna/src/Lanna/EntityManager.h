#pragma once

#include <list>
#include "GameObject/GameObject.h"

namespace Lanna
{

	class LANNA_API EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		void Init();
		void Update();
		void Render();

		void AddGameObject(GameObject* gameObject);
		GameObject* AddEmptyGameObject(const char* name);

		void DestroyGameObject(GameObject* gameObject);
		void SetActiveEntity(std::vector<uint64_t> *selection, int root);

		GameObject* GetActiveEntitiy() { return activeEntitiy; }
		std::vector<GameObject*>* GetEntityList() { return &m_Entities; }
	private:
		std::vector<GameObject*> m_Entities;
		GameObject* activeEntitiy = nullptr;
	};
}