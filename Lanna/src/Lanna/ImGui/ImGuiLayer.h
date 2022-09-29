#pragma once

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
		void OnEvent(Event& event) override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		
		void MainMenuBar();
	private:
		float m_Time = 0.0f;

		Panel* m_about = nullptr;
		Panel* m_configuration = nullptr;

		std::vector<Panel*> m_panels;
	};

}
