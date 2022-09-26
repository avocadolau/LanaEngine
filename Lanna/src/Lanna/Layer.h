#pragma once

#include "Lanna/Core.h"
#include "Lanna/Events/Event.h"

namespace Lanna {
	//to use this we subclass this class and implement what we want
	class LANNA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer"); //We have a layer which optionally takes in a name like a debug name
		virtual ~Layer();

		virtual void OnAttach() {} //When a layer is pushed on a layer stack and part of app, we attach it
		virtual void OnDetach() {} //We can detatch/remove it
		virtual void OnUpdate() {} //Gets called by app when layer is updated , every frame
		virtual void OnEvent(Event& event) {} //Whenever an event gets sent to layer, we recieve it here (all virtual so we can override)

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
