#pragma once

#ifdef LN_PLATFORM_WINDOWS

extern Lanna::Application* Lanna::CreateApplication();

int main(int argc, char** argv)
{
	printf("Lanna Engine");
	auto app = Lanna::CreateApplication();
	app->Run();
	delete app;
}


#endif