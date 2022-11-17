#pragma once

#include <optick.h>

#ifdef LN_PLATFORM_WINDOWS

extern Lanna::Application* Lanna::CreateApplication();

int main(int argc, char** argv)
{
	Lanna::Log::Init();
	LN_CORE_WARN("Initialized Log!");

	auto app = Lanna::CreateApplication();
	app->Run();
	delete app;
}

#endif