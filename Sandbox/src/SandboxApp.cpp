#include <Lanna.h>

class ExampleLayer : public Lanna::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Lanna::Input::IsKeyPressed(LN_KEY_TAB))
			LN_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Lanna::Event& event) override
	{
		if (event.GetEventType() == Lanna::EventType::KeyPressed)
		{
			Lanna::KeyPressedEvent& e = (Lanna::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LN_KEY_TAB)
				LN_TRACE("Tab key is pressed (event)!");
			LN_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Lanna::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Lanna::Application* Lanna::CreateApplication()
{
	return new Sandbox();
}