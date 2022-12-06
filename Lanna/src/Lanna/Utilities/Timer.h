#pragma once
#pragma warning(disable : 4251)
#include "Lanna/Core.h"
#include <iostream>
#include <chrono>

namespace Lanna {

	namespace Time {

		class Timer 
		{
			std::chrono::time_point<std::chrono::steady_clock> start, end;

			std::chrono::duration<float> duration;
		 public:
			Timer();
			~Timer();
		};

	}
}