#include "lnpch.h"
#include "Timer.h"

namespace Lanna {

	namespace Time
	{
		Timer::Timer()
		{
			start = std::chrono::high_resolution_clock::now();
		}

		Timer::~Timer()
		{
			end = std::chrono::high_resolution_clock::now();
			duration = end - start;

			float ms = duration.count() * 1000.0f;

			std::cout << "Time taken " << ms << " ms." << std::endl;
		}
	}
}