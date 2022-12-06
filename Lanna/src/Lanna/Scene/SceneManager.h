#pragma once
#include <Lanna/Core.h>
#include "Lanna/Scene/Scene.h"
#include <vector>
#include "Lanna/EntityManager.h"

typedef size_t SceneId;


namespace Lanna {

	class LANNA_API SceneManager {

	public:
		void Init();
		void Update();
		void Render();

		size_t CreateScene();
		SceneId getActiveSceneId() { return m_ActiveScene; }
		Scene* getActiveScene() { return m_Scene[m_ActiveScene]; }
		SceneId LoadScene(const char* scene_path);
	
	private:
		std::vector<Scene*> m_Scene;
		std::vector<Scene*> m_SceneList;
		SceneId m_ActiveScene;
		SceneManager();
	};
}
