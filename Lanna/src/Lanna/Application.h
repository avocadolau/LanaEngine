#pragma once

#include "Core.h"

#include "Window.h"
#include "Lanna/LayerStack.h"
#include "Lanna/Events/Event.h"
#include "Lanna/Events/ApplicationEvent.h"


namespace Lanna {

	class LANNA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		void OpenUrl(const char* url);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}