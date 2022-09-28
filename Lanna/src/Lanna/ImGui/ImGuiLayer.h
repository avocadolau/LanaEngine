#pragma once

#include "Lanna/Layer.h"

#include "Lanna/Events/ApplicationEvent.h"
#include "Lanna/Events/KeyEvent.h"
#include "Lanna/Events/MouseEvent.h"

namespace Lanna {

	class LANNA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		
		void UpdateMainMenu();
		void MainMenuBar();
	private:
		float m_Time = 0.0f;

		bool confMenu = false;


	};

}
