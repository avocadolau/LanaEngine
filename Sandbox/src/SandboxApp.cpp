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

};

Lanna::Application* Lanna::CreateApplication()
{
	return new Sandbox();
}