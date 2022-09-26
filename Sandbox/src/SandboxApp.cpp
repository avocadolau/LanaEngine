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
		LN_INFO("ExampleLayer::Update");
	}

	void OnEvent(Lanna::Event& event) override
	{
		LN_TRACE("{0}", event);
	}
};

class Sandbox : public Lanna::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Lanna::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Lanna::Application* Lanna::CreateApplication()
{
	return new Sandbox();
}