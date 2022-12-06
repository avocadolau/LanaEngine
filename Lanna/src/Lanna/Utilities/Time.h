#pragma once

#include "Lanna/Core.h"
#include <chrono>

namespace Lanna
{
	class Time
	{
	private:
		static std::chrono::time_point<std::chrono::steady_clock> m_GameClock;
		static std::chrono::time_point<std::chrono::steady_clock> m_RealTimeClock;
		static uint32_t m_FrameCount;
		static std::chrono::duration<float> m_Time;
		static int m_TimeScale;
		static std::chrono::duration<float> m_DeltaTime;
		static std::chrono::time_point<std::chrono::steady_clock> m_RealLastTime;
		static std::chrono::time_point<std::chrono::steady_clock> m_LastTime;
		static std::chrono::duration<float> m_RealTimeSinceStartup;
		static std::chrono::duration<float> m_RealTimeDeltaTime;
		static bool m_IsPlaying;
		static bool m_IsPaused;

	private:
		Time();

	public:
		static void Play();
		static void Update();
		static void Stop();
		static void Pause();

		static inline uint32_t GetFrameCount() { return m_FrameCount; }
		static inline float GetTime() { return m_Time.count(); }
		static inline int GetTimeScale() { return m_TimeScale; }

		static inline float GetDeltaTime() { return m_DeltaTime.count() * 1000.0f; }
		static inline float GetRealTimeSinceStartup() { return m_RealTimeSinceStartup.count(); }
		static inline float GetRealDeltaTime() { return m_RealTimeDeltaTime.count() * 1000.0f; }

		static inline bool IsPlaying() { return m_IsPlaying; }
		static void SetTimeScale(const int value);
	};
}
