#pragma once

#include "Core.h"

namespace Lanna {

	class LN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}