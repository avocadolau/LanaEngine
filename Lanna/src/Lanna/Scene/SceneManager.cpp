#include "lnpch.h"
#include "SceneManager.h"
#include "Lanna/EntityManager.h"

namespace Lanna {

	void SceneManager::Init()
	{

	}

	void SceneManager::Update()
	{
		m_SceneList[m_ActiveScene]->Update();
	}

	void SceneManager::Render()
	{
		m_SceneList[m_ActiveScene]->Render();
	}

	size_t SceneManager::CreateScene()
	{
		SceneId scene_id = m_SceneList.size();
		Scene* sc = new Scene();
		m_SceneList.push_back(sc);
		sc->Init();
		return scene_id;
	}
	
	SceneId SceneManager::LoadScene(const char* scene_path)
	{
		return SceneId();
	}
	
}

