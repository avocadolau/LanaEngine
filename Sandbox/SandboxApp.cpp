#include <Lanna.h>

class Sandbox : public Lanna::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

	void Run()
	{

	}
};

Lanna::Application* Lanna::CreateApplication()
{
	return new Sandbox();
}

