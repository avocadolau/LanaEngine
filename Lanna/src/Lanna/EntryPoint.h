#pragma once

#ifdef LN_PLATFORM_WINDOWS

extern Lanna::Application* Lanna::CreateApplication();

int main(int argc, char** argv)
{
	Lanna::Log::Init();
	LN_CORE_WARN("Initialized Log!");
	int a = 5;
	LN_INFO("Hello! Var={0}", a);

	auto app = Lanna::CreateApplication();
	app->Run();
	delete app;
}

#endif