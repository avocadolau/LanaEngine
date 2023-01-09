#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <optick.h>

#include <filesystem>

#include "Lanna/Log.h"

#ifdef LN_PLATFORM_WINDOWS
#include <Windows.h>
#endif


// DEBUG DEFINES

#define MAX_BONES_PER_VERTEX 6

#define DEBUG_ANIM