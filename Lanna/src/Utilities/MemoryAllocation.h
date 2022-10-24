#pragma once
#include <cstdlib>

namespace Lanna {
	// Allocation metrics
	struct AllocationMetrics {
		static size_t allocation_count;
		static size_t bytes_allocated;
	};

	size_t AllocationMetrics::allocation_count = 0;
	size_t AllocationMetrics::bytes_allocated = 0;
}

// Allocation overloads
void* operator new(size_t size) {
	Lanna::AllocationMetrics::allocation_count++;
	Lanna::AllocationMetrics::bytes_allocated += size;

	return malloc(size);
}

void operator delete(void* memory, size_t size) {
	Lanna::AllocationMetrics::allocation_count--;
	Lanna::AllocationMetrics::bytes_allocated -= size;

	free(memory);
}