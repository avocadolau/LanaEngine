#pragma once

#include "Core.h"

#include "Window.h"
#include "Lanna/LayerStack.h"
#include "Lanna/ImGui/ImGuiLayer.h"
#include "Lanna/Events/Event.h"
#include "Lanna/Events/ApplicationEvent.h"
#include "Render3D.h"
#include "EntityManager.h"


namespace Lanna {

	struct SysInfo
	{
		char glfwVer[32];
		uint32_t cache;
		uint32_t numCores;
		float ram;
		const unsigned char* gpu;
		const unsigned char* gpuBrand;
		float gpuVRAM;
		float gpuVRAMUsage;
		float gpuVRAMAV;
		float gpuVRAMReserve;
	};

	class LANNA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void SetHwInfo();
		void Close();

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		inline SysInfo& GetSystemInfo() { return m_SysInfo; }
		inline EntityManager* GetEntityManager() { return m_EntityManager; }
		inline Render3D& GetRenderer() { return *m_Render3D; }

		void OpenUrl(const char* url);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		SysInfo m_SysInfo;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		Render3D* m_Render3D;
		EntityManager* m_EntityManager;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}