#pragma once

#include "../Shared/os.hpp"

namespace crossover {
namespace monitor {
namespace client {
namespace os {
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;
/**
 * Gets the number of currently running processes.
 */
unsigned process_count() noexcept;
/**
 * Gets CPU use percentage (0 to 100).
 */
float cpu_use_percent() noexcept;
/**
 * Gets physical memory use percentage (0 to 100).
 */
float memory_use_percent() noexcept;
int64_t getTotalPhysicalMemory();
float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);

} //namespace os
} //namespace client
} //namespace monitor
} //namespace crossover
