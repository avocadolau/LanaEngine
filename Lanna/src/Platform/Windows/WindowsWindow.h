#pragma once

#include "Lanna/Window.h"

#include <GLFW/glfw3.h>

namespace Lanna {

	class WindowsWindow : public Window
	{
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height, Refresh;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		bool m_FullScreen = false;
		bool m_Resizable = false;

		WindowData m_Data;
		WindowData m_OldData;
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline WindowData& GetWindowData() { return m_Data; }

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		virtual bool GetFullScreen() const override { return m_FullScreen; };
		virtual bool GetResizable() const override { return m_Resizable; };

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual void SetWidth(int val) override;
		virtual void SetHeight(int val) override;
		virtual void SetFullScreen(bool enabled) override;
		virtual void SetResizable(bool enabled) override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	
	};

}