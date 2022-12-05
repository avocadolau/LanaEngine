#pragma once
#include <Lanna/Core.h>
#include "Lanna/Scene/Scene.h"
#include <vector>


namespace Lanna {

	class LANNA_API SceneManager {

	public:
		void Init();
		void Update();
		void Render();

		size_t CreateScene();
	

	private:
		std::vector<Scene> m_SceneList;
		size_t m_ActiveScene;
	};
}
