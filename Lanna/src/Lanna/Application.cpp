#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Lanna {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		LN_TRACE(e);

		while (true);
	}

}