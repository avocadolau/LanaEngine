#pragma once
#include <Lanna/Core.h>
#include "Lanna/EntityManager.h"


namespace Lanna {



	class LANNA_API Scene {
		
	public:
		void Update();
	private:
		EntityManager m_EntityManager;
	};
}
