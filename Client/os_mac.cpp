#include "os.hpp"

#include "log.hpp"
#include <vector>
#include <mutex>
#include <thread>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#define LOG CROSSOVER_MONITOR_LOG

using namespace std;

namespace crossover {
    namespace monitor {
        namespace client {
            namespace os {
                unsigned process_count() noexcept {
                    return 1;
                }
                float cpu_use_percent() noexcept {
                    host_cpu_load_info_data_t cpuinfo;
                    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
                    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS) {
                        unsigned long long totalTicks = 0;
                        for(int i=0; i<CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
                            return CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks)*100;
                    }
                    else return -1.0f;
                }
                float memory_use_percent() noexcept {
                    vm_size_t page_size;
                    mach_port_t mach_port;
                    mach_msg_type_number_t count;
                    vm_statistics64_data_t vm_stats;
                    mach_port = mach_host_self();
                    count = sizeof(vm_stats) / sizeof(natural_t);
                    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
                        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                                          (host_info64_t)&vm_stats, &count))
                    {
                        //long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;
                        long long used_memory = ((int64_t)vm_stats.active_count +
                                                 (int64_t)vm_stats.inactive_count +
                                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
                        return (float)((used_memory*100)/os::getTotalPhysicalMemory());
                    }
                    return 0;
                }
                int64_t getTotalPhysicalMemory(){
                    int mib[2];
                    int64_t physical_memory;
                    mib[0] = CTL_HW;
                    mib[1] = HW_MEMSIZE;
                    size_t length = sizeof(int64_t);
                    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
                    return physical_memory;
                }
                float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
                {
                    unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
                    unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;
                    float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);
                    _previousTotalTicks = totalTicks;
                    _previousIdleTicks  = idleTicks;
                    return ret;
                }
            } //namespace os
        } //namespace client
    } //namespace monitor
} //namespace crossover

