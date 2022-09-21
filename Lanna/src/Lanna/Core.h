#pragma once

#ifdef LN_PLATFORM_WINDOWS
	#ifdef LN_BUILD_DLL
		#define LANNA_API __declspec(dllexport)
	#else
		#define LANNA_API __declspec(dllimport)
	#endif
#else
	#error Lanna only supports Windows!
#endif