#include "lnpch.h"
#include "SceneManager.h"
#include "Lanna/EntityManager.h"

namespace Lanna {

	void SceneManager::Init()
	{
	}

	void SceneManager::Update()
	{
		m_Scene[m_ActiveScene]->Update();
	}

	void SceneManager::Render()
	{
	}

	size_t SceneManager::CreateScene()
	{
		return size_t();
	}
	
	SceneId SceneManager::LoadScene(const char* scene_path)
	{
		return SceneId();
	}
	
	
}

