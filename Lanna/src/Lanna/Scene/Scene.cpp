#include "lnpch.h"
#include "Scene.h"


namespace Lanna {

	Scene::Scene()
	{

	}

	void Scene::Init()
	{
		m_EntityManager.Init();
	}

	void Scene::Update()
	{
		m_EntityManager.Update();
	}

	void Scene::Render()
	{
		m_EntityManager.Render();
	}

	EntityManager* Scene::GetEntityManager()
	{
		return &m_EntityManager;
	}
}
