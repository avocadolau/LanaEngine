#pragma once

#include "Lanna/ImGui/ImGuiLog.h"
#include "Lanna/Layer.h"

#include "Lanna/Events/ApplicationEvent.h"
#include "Lanna/Events/KeyEvent.h"
#include "Lanna/Events/MouseEvent.h"

#include "Lanna/ImGui/Panels/Panel.h"

#include <vector>

namespace Lanna {

	class LANNA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;

		void Begin();
		void End();

		void OnEvent(Event& event) override;
		void OnImGuiRender() override;

		inline void LogTrace(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::TRACE, log); }
		inline void LogInfo(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::INFO, log); }
		inline void LogWarn(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::WARN, log); }
		inline void LogError(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::ERR, log); }
		inline void LogCritical(const char* log) { m_Log.AddLog(ImGuiLog::LogLevel::FATAL, log); }

		inline ImGuiLog& GetLog() { return m_Log; }

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		void MainMenuBar();
		void DockSpace();

	private:
		ImGuiLog m_Log;
		bool logActive;

		float m_Time = 0.0f;

		Panel* m_about = nullptr;
		Panel* m_configuration = nullptr;
		Panel* m_hardware = nullptr;
		Panel* m_scene = nullptr;
		Panel* m_Inspector = nullptr;
		Panel* m_Hierarchy = nullptr;
		Panel* m_Assets = nullptr;

		std::vector<Panel*> m_panels;

	};

}
