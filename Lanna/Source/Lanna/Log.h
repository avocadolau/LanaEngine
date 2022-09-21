#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
//#include "spdlog/fmt/ostr.h"

namespace Lanna {

	class LN_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


// Core log macros
#define LN_CORE_TRACE(...)  ::Lanna::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LN_CORE_INFO(...)   ::Lanna::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LN_CORE_WARN(...)   ::Lanna::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LN_CORE_ERROR(...)  ::Lanna::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LN_CORE_FATAL(...)  ::Lanna::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// Client log macros
#define LN_TRACE(...)  ::Lanna::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LN_INFO(...)   ::Lanna::Log::GetClientLogger()->info(__VA_ARGS__)
#define LN_WARN(...)   ::Lanna::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LN_ERROR(...)  ::Lanna::Log::GetClientLogger()->error(__VA_ARGS__)
#define LN_FATAL(...)  ::Lanna::Log::GetClientLogger()->fatal(__VA_ARGS__)
