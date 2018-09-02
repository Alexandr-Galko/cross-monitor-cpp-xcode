#include "os.hpp"
#include "log.hpp"
#include <mutex>
#include <thread>
#include <signal.h>

#define LOG CROSSOVER_MONITOR_LOG

using namespace std;

namespace crossover {
    namespace monitor {
        namespace os {
            static mutex mutex_;
            function<void()> handler_;
            
            void handler_helper(int type) {
                LOG(info) << "Received event of type " + std::to_string(type) +"   "+std::to_string(2);
                switch (type) {
                    case 2:
                        LOG(info) << "calling handle_";
                        try {
                            lock_guard<mutex> lock(mutex_);
                            if (handler_) {
                                handler_();
                            }
                        } catch (const std::exception& e) {
                            LOG(error) << "Termination handler threw an exception: "
                            << e.what();
                        } catch (...) {
                            LOG(error) << "Termination handler threw an unknown exception: ";
                        }
                }
            }
            
            void set_termination_handler(const std::function<void()>& handler) noexcept {
                lock_guard<mutex> lock(mutex_);
                struct sigaction sigIntHandler;
                handler_ = handler;
                sigIntHandler.sa_handler = handler_helper;
                sigemptyset(&sigIntHandler.sa_mask);
                sigIntHandler.sa_flags = 0;
                sigaction(SIGINT, &sigIntHandler, NULL);
            }
            
        } //namespace os
    } //namespace monitor
} //namespace crossover

