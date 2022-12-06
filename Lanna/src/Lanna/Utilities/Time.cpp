#include "lnpch.h"
#include "Time.h"

namespace Lanna
{

	std::chrono::time_point<std::chrono::steady_clock> Time::m_RealTimeClock = std::chrono::high_resolution_clock::now();
	uint32_t Time::m_FrameCount = 0;
	int Time::m_TimeScale = 1;
	bool Time::m_IsPlaying = false;
	bool Time::m_IsPaused = false;

	std::chrono::time_point<std::chrono::steady_clock> Time::m_GameClock;
	std::chrono::duration<float>  Time::m_Time;
	std::chrono::duration<float>  Time::m_DeltaTime;
	std::chrono::time_point<std::chrono::steady_clock>  Time::m_RealLastTime;
	std::chrono::time_point<std::chrono::steady_clock>  Time::m_LastTime;
	std::chrono::duration<float>  Time::m_RealTimeSinceStartup;
	std::chrono::duration<float>  Time::m_RealTimeDeltaTime;

	void Time::Play()
	{
		m_IsPlaying = true;
		m_GameClock = std::chrono::high_resolution_clock::now();
		m_TimeScale = 1;
	}

	void Time::Update()
	{
		m_FrameCount++;
		m_RealTimeDeltaTime = std::chrono::high_resolution_clock::now() - m_RealLastTime;
		m_RealLastTime = std::chrono::high_resolution_clock::now();
		m_RealTimeSinceStartup = std::chrono::high_resolution_clock::now() - m_RealTimeClock;
		if (m_IsPlaying)
		{
			if (m_IsPaused) return;
			m_DeltaTime = (std::chrono::high_resolution_clock::now() - m_LastTime) * m_TimeScale;
			m_LastTime = std::chrono::high_resolution_clock::now();
			m_Time = std::chrono::high_resolution_clock::now() - m_GameClock;
		
		}


	}

	void Time::Stop()
	{
		m_IsPlaying = false;
		m_TimeScale = 0;
	}

	void Time::Pause()
	{
		m_IsPaused = !m_IsPaused;
	}

	void Time::SetTimeScale(const int value)
	{
		m_TimeScale = value;
		//CLAMP(m_TimeScale, -2, 5);
	}

}