#pragma once

#include "lnpch.h"

#include "Lanna/Core.h"
#include "Lanna/Events/Event.h"

namespace Lanna {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		unsigned int Refresh;

		WindowProps(const std::string& title = "Lanna Engine",
			unsigned int width = 1280,
			unsigned int height = 720,
			unsigned int refresh =144)
			: Title(title), Width(width), Height(height), Refresh(refresh)
		{
		}
	};

	// Interface representing a desktop system based Window
	class LANNA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual bool GetFullScreen() const = 0;
		virtual bool GetResizable() const = 0;

		virtual void* GetNativeWindow() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetWidth(int val) = 0;
		virtual void SetHeight(int val) = 0;
		virtual void SetFullScreen(bool enabled) = 0;
		virtual void SetResizable(bool enabled) = 0;


		static Window* Create(const WindowProps& props = WindowProps());
	};

}