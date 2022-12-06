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
		Scene* getActiveScene() { return m_SceneList[m_ActiveScene]; }
		void setActiveScene(SceneId _sceneId) { m_ActiveScene = _sceneId; };
		SceneId LoadScene(const char* scene_path);
	
	private:
		std::vector<Scene*> m_SceneList;
		SceneId m_ActiveScene;
	};
}
