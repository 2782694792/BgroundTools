#ifndef MULTI_THREAD_MUTEX_H
#define MULTI_THREAD_MUTEX_H

#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "timer.hpp"

using LL      = long long;
static LL sum = 0;
using namespace belien;

class thread_mutex {
private:
    std::mutex m_mutex;

public:
    thread_mutex() {}
    ~thread_mutex() {}

    void concurrent_worker(int minV, int maxV) {
        LL tmp_sum = 0;
        for (int i = minV; i <= maxV; i++) {
            tmp_sum += i * ( LL )i;
        }
        m_mutex.lock();
        sum += tmp_sum;
        m_mutex.unlock();
    }

    void concurrent_task(int minV, int maxV) {
        Timer    timer;
        int concurrent_count = std::thread::
            hardware_concurrency(); // 获取当前硬件支持多少个线程并发执行
        std::cout << "hardware_concurrency: " << concurrent_count << std::endl;
        std::vector< std::thread > threads;
        minV = 0;
        sum  = 0;
        for (int t = 0; t < concurrent_count; t++) {
            int range = maxV / concurrent_count * (t + 1);
            threads.push_back(std::thread(&thread_mutex::concurrent_worker, this, minV, range));
            minV = range + 1;
        }
        for (auto& t : threads) {
            t.join();
        }
        std::cout << "concurrency task finish, " << timer.getMilliSeconds()
                  << " ms consumed, Result:" << std::fixed
                  << std::setprecision(3) << sum << std::endl;
    }
};


#endif
