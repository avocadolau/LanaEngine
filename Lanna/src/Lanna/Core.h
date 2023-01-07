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

#ifdef LN_DEBUG
	#define LN_ENABLE_ASSERTS
#endif

#ifdef LN_ENABLE_ASSERTS
	//#define LN_ASSERT(x, ...) { if(!(x)) { LN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LN_CORE_ASSERT(x, ...) { if(!(x)) { LN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	//#define LN_ASSERT(x, ...)
	#define LN_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define LN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define CLAMP(x, mn, mx) (x) < (mn) ? (x) = (mn) : (x) = (x); (x) > (mx) ? (x) = (mx) : (x) = (x)



//namespace Lanna {
//
//	template<typename T>
//	using Scope = std::unique_ptr<T>;
//
//	template<typename T>
//	using Ref = std::shared_ptr<T>;
//
//}
