#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "imgui.h"

namespace Lanna {

    enum LogLevel {
        TRACE,
        INFO,
        WARN,
        ERR,
        FATAL,
        NONE
    };

	class LANNA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		//inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		static const char* GetCoreLastLog();
		static const char* GetClientLastLog();

		static void ImGuiLogTrace(const char* log);
		static void ImGuiLogInfo(const char* log);
		static void ImGuiLogWarn(const char* log);
		static void ImGuiLogError(const char* log);
		static void ImGuiLogCritical(const char* log);

		static void ImGuiConsoleTrace(const char* log);
		static void ImGuiConsoleInfo(const char* log);
		static void ImGuiConsoleWarn(const char* log);
		static void ImGuiConsoleError(const char* log);
		static void ImGuiConsoleCritical(const char* log);
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		//static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


    class LANNA_API AppConsole
    {
    private:
        char                  InputBuf[256];
        ImVector<char*>       Items;
        ImVector<const char*> Commands;
        ImVector<char*>       History;
        int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter       Filter;
        bool                  AutoScroll;
        bool                  ScrollToBottom;

        static AppConsole* console_Instance;
    public:

        AppConsole();
        ~AppConsole();

        // Portable helpers
        static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
        static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
        static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
        static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

        void ClearLog();
        void AddLog(LogLevel logLevel, const char* fmt, ...);
        void Draw(const char* title, bool* p_open);
        void ExecCommand(const char* command_line);
        // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
        static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
        int TextEditCallback(ImGuiInputTextCallbackData* data);
        static AppConsole& Get() { return *console_Instance; }
    };

}



// Core log macros
#define LN_CORE_TRACE(...)      ::Lanna::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define LN_CORE_INFO(...)       ::Lanna::Log::GetCoreLogger()->info(__VA_ARGS__); 
#define LN_CORE_WARN(...)       ::Lanna::Log::GetCoreLogger()->warn(__VA_ARGS__); 
#define LN_CORE_ERROR(...)      ::Lanna::Log::GetCoreLogger()->error(__VA_ARGS__);
#define LN_CORE_CRITICAL(...)      ::Lanna::Log::GetCoreLogger()->critical(__VA_ARGS__); 

// editor logs
#define _LN_TRACE(...) ::Lanna::AppConsole::Get().AddLog(Lanna::LogLevel::TRACE, __VA_ARGS__);
#define _LN_INFO(...) ::Lanna::AppConsole::Get().AddLog(Lanna::LogLevel::INFO, __VA_ARGS__);
#define _LN_WARN(...) ::Lanna::AppConsole::Get().AddLog(Lanna::LogLevel::WARN, __VA_ARGS__);
#define _LN_ERROR(...) ::Lanna::AppConsole::Get().AddLog(Lanna::LogLevel::ERR, __VA_ARGS__);
#define _LN_CRITICAL(...) ::Lanna::AppConsole::Get().AddLog(Lanna::LogLevel::FATAL, __VA_ARGS__);