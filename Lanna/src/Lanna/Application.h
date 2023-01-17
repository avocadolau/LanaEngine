#pragma once

#include "Core.h"

#include "Window.h"
#include "Lanna/LayerStack.h"
#include "Lanna/ImGui/ImGuiLayer.h"
#include "Lanna/Events/Event.h"
#include "Lanna/Events/ApplicationEvent.h"
#include "Render3D.h"
#include "EntityManager.h"
#include "Scene/SceneManager.h"
#include "AnimManager.h"
#include "Resources.h"
#include "Lanna/Utilities/Time.h"

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
		inline SceneManager* GetSceneManager() { return m_SceneManager; }
		inline Render3D& GetRenderer() { return *m_Render3D; }
		inline Resources& GetResources() { return *m_Resources; }
		inline AnimManager& GetAnimMan() { return *m_AnimManager; }
		inline Time& GetTime() { return *m_Time; }

		void OpenUrl(const char* url);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		SysInfo m_SysInfo;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		Render3D* m_Render3D;
		SceneManager* m_SceneManager;
		Console* m_Console;
		Resources* m_Resources;
		AnimManager* m_AnimManager;
		Time* m_Time;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

// module getters
#define LN_ENTITY_MAN ::Lanna::Application::Get().GetSceneManager()->getActiveScene()->GetEntityManager()
#define LN_SCENE_MAN ::Lanna::Application::Get().GetSceneManager()
#define LN_RENDERER ::Lanna::Application::Get().GetRenderer()
#define LN_RESOURCES ::Lanna::Application::Get().GetResources()
#define LN_ANIMATIONS ::Lanna::Application::Get().GetAnimMan()