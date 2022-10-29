#pragma once
#include <cstdlib>

namespace Lanna {
	// Allocation metrics
	struct MemoryAllocation {
		static size_t allocation_count;
		static size_t bytes_allocated;
	};

	size_t MemoryAllocation::allocation_count = 0;
	size_t MemoryAllocation::bytes_allocated = 0;
}

// Allocation overloads
void* operator new(size_t size) {
	Lanna::MemoryAllocation::allocation_count++;
	Lanna::MemoryAllocation::bytes_allocated += size;

	return malloc(size);
}

void operator delete(void* memory, size_t size) {
	Lanna::MemoryAllocation::allocation_count--;
	Lanna::MemoryAllocation::bytes_allocated -= size;

	free(memory);
}