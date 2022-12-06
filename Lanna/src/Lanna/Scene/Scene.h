#pragma once
#include <Lanna/Core.h>
#include "Lanna/EntityManager.h"


namespace Lanna {

	class LANNA_API Scene {
		
	public:
		Scene();
		~Scene();

		void Init();
		void Update();
		void Render();

		EntityManager* GetEntityManager();

	private:

		EntityManager m_EntityManager;
	};
}
