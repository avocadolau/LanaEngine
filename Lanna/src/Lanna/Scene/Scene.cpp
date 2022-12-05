#include "lnpch.h"
#include "Scene.h"


namespace Lanna {

	void Lanna::Scene::Update()
	{
		m_EntityManager.Update();

	}

	EntityManager* Lanna::Scene::GetEntityManager()
	{
		return nullptr;
	}

}
