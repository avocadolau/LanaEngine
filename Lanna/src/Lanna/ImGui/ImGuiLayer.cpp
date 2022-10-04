#include "lnpch.h"
#include "ImGuiLayer.h"

//#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"

#include "Lanna/Application.h"

#define IMGUI_IMP_API

// PANELS
#include <vector>

#include "Lanna/ImGui/Panels/Panel.h"
#include "Lanna/ImGui/Panels/AboutPanel.h"
#include "Lanna/ImGui/Panels/ConfigurationPanel.h"
#include "Lanna/ImGui/Panels/HardwarePanel.h"
#include "Lanna/ImGui/Panels/ScenePanel.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glew.h>

namespace Lanna {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		IMGUI_CHECKVERSION();
		//Set some flags
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();


		// TEMPORARY: should use Lanna key codes
		/*io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;*/


		// panels --------------------------------
		m_configuration = new ConfigurationPanel();
		m_about = new AboutPanel();
		m_hardware = new HardwarePanel();
		m_scene = new ScenePanel();

		m_panels.push_back(m_configuration);
		m_panels.push_back(m_about);
		m_panels.push_back(m_hardware);
		m_panels.push_back(m_scene);

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		delete m_about;
		m_panels.clear();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{

		

		// panels ------------------------
		MainMenuBar();
		for (auto p : m_panels)
		{
			if (p->active)
				p->Draw();
		}
		if (logActive)
			m_Log.Draw("Console", &logActive);

		/*static bool show = true;
		ImGui::ShowDemoWindow(&show);*/
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();  //Give us our APP
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight()); //Shows Im gui our display is

		// RENDER
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	void ImGuiLayer::MainMenuBar()
	{
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("View"))
		{
			for (auto p : m_panels)
			{
				if (ImGui::MenuItem(p->GetName(), "", p->active))
					p->SwitchActive();
			}
			ImGui::MenuItem("Console", "", &logActive);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Demo"))
				Lanna::Application::Get().OpenUrl("https://google.com/");

			if (ImGui::MenuItem("Documentation"))
				Lanna::Application::Get().OpenUrl("https://google.com/");

			if (ImGui::MenuItem("Download latest"))
				Lanna::Application::Get().OpenUrl("https://google.com/");

			if (ImGui::MenuItem("Report a bug"))
				Lanna::Application::Get().OpenUrl("https://google.com/");

			if (ImGui::MenuItem("About"))
				Lanna::Application::Get().OpenUrl("https://google.com/");

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

