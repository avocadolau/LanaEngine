#include "lnpch.h"
#include "Application.h"

#include "Log.h"

#include <glew.h>

#include "Input.h"
#include "imgui.h"
#include "Render3D.h"
#include "Resources.h"

#include <Windows.h>
#include <shellapi.h>


#ifdef DEBUG_ANIM
#include "Lanna/Resources/Animation.h"
#include "Lanna/Resources/Skeleton.h"
#endif // DEBUG_ANIM\



#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049
#define GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX 0x904B

namespace Lanna {

 #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		LN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Console = new Console();
		m_Console->Init();

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		SetHwInfo();

		m_Resources = new Resources();
		m_SceneManager = new SceneManager();
		m_Render3D = new Render3D();
		m_ImGuiLayer = new ImGuiLayer();
		m_AnimManager = new AnimManager();

		size_t newVar = m_SceneManager->CreateScene();
		m_SceneManager->setActiveScene(newVar);
		m_Render3D->Init();
		m_AnimManager->Init();
		PushOverlay(m_ImGuiLayer);

#ifdef DEBUG_ANIM
		//LN_RESOURCES.Import<Animation>("resources/animations/test.FBX");
		LN_RESOURCES.Import<Skeleton>("resources/animations/test.FBX");
#endif // DEBUG_ANIM


	}

	Application::~Application()
	{
		
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::SetHwInfo()
	{
		SYSTEM_INFO info;
		::GetSystemInfo(&info);

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		GLint total_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, &total_mem_kb);
		GLint cur_avail_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &cur_avail_mem_kb);
		GLint cur_reserv_mem_kb = 0;
		glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &cur_reserv_mem_kb);

		m_SysInfo.numCores = info.dwNumberOfProcessors;
		m_SysInfo.ram = memInfo.ullTotalPhys >> 20;
		m_SysInfo.gpu = glGetString(GL_VENDOR);
		m_SysInfo.gpuBrand = glGetString(GL_RENDERER);
		m_SysInfo.gpuVRAM = total_mem_kb >> 10;
		m_SysInfo.gpuVRAMAV = cur_avail_mem_kb >> 10;
		m_SysInfo.gpuVRAMUsage = (total_mem_kb - cur_avail_mem_kb) >> 10;
		m_SysInfo.gpuVRAMReserve = cur_reserv_mem_kb >> 10;
	}

	void Application::Close()
	{
		m_Running = false;
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{

			OPTICK_FRAME("Application Loop")
			OPTICK_EVENT()
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//m_Render3D->Update();


			m_Render3D->Update();
			m_SceneManager->Update();
			m_AnimManager->Update();
			m_SceneManager->Render();
			m_AnimManager->Render();

			Time::Update();

			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OpenUrl(const char* url)
	{
		ShellExecuteA(0, "open", url, NULL, NULL, SW_SHOWNORMAL);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}