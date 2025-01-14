#include "lnpch.h"
#include "ImGuiLayer.h"

//#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"

#include "Lanna/Application.h"
#include "Lanna/EntityManager.h"

#define IMGUI_IMP_API

// PANELS
#include <vector>

#include "Lanna/ImGui/Panels/Panel.h"
#include "Lanna/ImGui/Panels/AboutPanel.h"
#include "Lanna/ImGui/Panels/ConfigurationPanel.h"
#include "Lanna/ImGui/Panels/HardwarePanel.h"
#include "Lanna/ImGui/Panels/ScenePanel.h"
#include "Lanna/ImGui/Panels/InspectorPanel.h"
#include "Lanna/ImGui/Panels/HierarchyPanel.h"
#include "Lanna/ImGui/Panels/AssetsPanel.h"
#include "Lanna/ImGui/Panels/GameScenePanel.h"
#include "Lanna/ImGui/Panels/AnimationPanel.h"
#include "Lanna/GameObject/Components/MeshComponent.h"

#include "Lanna/Render3D.h"
#include <gtc/matrix_transform.hpp>
#include "Lanna/Input.h"
#include "Lanna/KeyCodes.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glew.h>
#include <glm.hpp>

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

		io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
		io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;

		ImGui::StyleColorsDark();

		m_IconPlay = new Texture();
		m_IconPlay->Init("resources/icons/PlayButton.png");
		m_IconStop = new Texture();
		m_IconStop->Init("resources/icons/StopButton.png");
		m_IconPause = new Texture();
		m_IconPause->Init("resources/icons/PauseButton.png");

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
		m_Inspector = new InspectorPanel();
		m_Hierarchy = new HierarchyPanel();
		m_Assets = new AssetsPanel();
		m_GameScene = new GameScenePanel();
		m_Animation = new AnimPanel();

		m_panels.push_back(m_configuration);
		m_panels.push_back(m_about);
		m_panels.push_back(m_hardware);
		m_panels.push_back(m_scene);
		m_panels.push_back(m_Hierarchy);
		m_panels.push_back(m_Inspector);
		m_panels.push_back(m_Assets);
		m_panels.push_back(m_GameScene);
		m_panels.push_back(m_Animation);

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGuiLayer::OnDetach()
	{
		delete m_about;
		m_panels.clear();

		delete m_IconPlay;
		delete m_IconStop;
		delete m_IconPause;

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		OPTICK_FRAME("OnUpdate");
		OPTICK_EVENT();

		DockSpace();

		ImGuiIO& io = ImGui::GetIO();
		
		

		// panels ------------------------
		//MainMenuBar();
		for (auto p : m_panels)
		{
			if (p->active)
				p->Draw();
		}

		if (logActive)
		{
			Console::Get().Render("Console app", &logActive);
		}
		
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::SaveAScene()
	{
	}

	void ImGuiLayer::OpenAScene()
	{
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

	void ImGuiLayer::OnEvent(Event& event)
	{
		OPTICK_EVENT();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(LN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(LN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(LN_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(LN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(LN_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	void ImGuiLayer::OnImGuiRender()
	{
		OPTICK_FRAME("OnImguiRender");
		OPTICK_EVENT();
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
		io.MousePosPrev = io.MousePos;
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		//LN_RENDERER.GetActiveCamera().ProcessMouseMovement(e.GetX(), e.GetY(), true);
		LN_RENDERER.GetActiveCamera().ProcessMouseMovement(e.GetX(), e.GetY(), true);

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		LN_RENDERER.GetActiveCamera().ProcessMouseScroll(e.GetYOffset());

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
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene"))
			{
				size_t active = LN_SCENE_MAN->CreateScene();
				LN_SCENE_MAN->setActiveScene(active);
			}
			if (ImGui::MenuItem("Open Scene"))
			{
				/*std::string filePath = Lanna::FileDialogs::OpenFile("Scene (*.scene)\0*.scene\0");
				if (!filePath.empty())
				{
					SceneId scene_id = Lanna::SceneManager::LoadScene(filePath.c_str());
					Lanna::SceneManager::SetScene(scene_id);
					LN_INFO("Succesfully opened project at path {0}", filePath.c_str());
				}*/
				
			}
			if (ImGui::MenuItem("Save Scene"))
			{

			}
			if (ImGui::MenuItem("Quit"))
			{
				Lanna::Application::Get().Close();
			}

			ImGui::EndMenu();
		}

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
		if (ImGui::BeginMenu("Primitives"))
		{
			const char* names[] = { "Cube", "Pyramid","Plane" };

			for (int i = 0; i < (int)Primitives::TOTAL_; i++)
			{
				if (ImGui::MenuItem(names[i]))
				{
					GameObject* obj = LN_ENTITY_MAN->AddEmptyGameObject(names[i]);
					MeshComponent* mesh= (MeshComponent*)obj->AddComponent(Component::Type::MESH);
					mesh->LoadPrimitive((Primitives)i);
					obj->AddComponent(Component::Type::MATERIAL);
					//obj->m_Material->setColor(glm::vec4(1.0f,0.0f,0.0f,1.0f));
				}
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{

			if (ImGui::MenuItem("Documentation"))
				Lanna::Application::Get().OpenUrl("https://github.com/avocadolau/LannaEngine/Wiki");

			if (ImGui::MenuItem("Download latest"))
				Lanna::Application::Get().OpenUrl("https://github.com/avocadolau/LannaEngine/releases");

			if (ImGui::MenuItem("Report a bug"))
				Lanna::Application::Get().OpenUrl("https://github.com/avocadolau/LannaEngine/issues");

			

			ImGui::EndMenu();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, { 0,0,0,0 });
		ImGui::SetCursorPosX(Lanna::Application::Get().GetWindow().GetWidth() / 2 - 15.0f);
		ImTextureID play = Lanna::Time::IsPlaying() ? (ImTextureID)(intptr_t) m_IconStop->GetTextureId() : (ImTextureID)(intptr_t) m_IconPlay->GetTextureId();
		if (ImGui::ImageButton(play, { 15, 15 }))
		{
			if (!Lanna::Time::IsPlaying())
				Lanna::Time::Play();
			else
				Lanna::Time::Stop();
		}

		if (ImGui::ImageButton((ImTextureID)(intptr_t) m_IconPause->GetTextureId(), { 15, 15 }))
		{
			Lanna::Time::Pause();
		}

		if (Lanna::Time::IsPlaying())
		{
			ImGui::Text(" %.2fs", Lanna::Time::GetTime());
		}


		ImGui::PopStyleColor();
		
	}

	void ImGuiLayer::DockSpace()
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar |ImGuiWindowFlags_NoDocking ;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::Begin("Lanna Engine", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar(2);



		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			//if (ImGui::BeginMenu("Docking"))
			//{
			//	// Disabling fullscreen would allow the window to be moved to the front of other windows,
			//	// which we can't undo at the moment without finer window depth/z control.
			//	ImGui::Separator();

			//	if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			//	if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			//	if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			//	if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			//	if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }

			//	ImGui::EndMenu();
			//}
			MainMenuBar();
			ImGui::EndMenuBar();
		}
		
		dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		
		ImGui::End();

		

	}
}