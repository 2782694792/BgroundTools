#ifndef MULTI_WAIT_JOIN_H
#define MULTI_WAIT_JOIN_H

#include <condition_variable> // std::condition_variable
#include <functional>
#include <iostream>           // std::cout
#include <mutex>              // std::mutex, std::unique_lock
#include <thread>             // std::thread, std::this_thread::yield

class thread_wait {
public:
    thread_wait();
    ~thread_wait();

    std::mutex              mtx;
    std::condition_variable cv;
    int                     cargo = 0;

    bool shipment_available() {
        return cargo != 0;
    }

    void consume(int n) {
        for (int i = 0; i < n; ++i) {
            std::unique_lock< std::mutex > lck(mtx); // 自动上锁
            // 第二个参数为false才阻塞（wait），阻塞完即unlock，给其它线程资源
            cv.wait(lck, std::bind(&thread_wait::shipment_available, this));
            std::cout << cargo << '\n';
            // 改变条件变量，让出线程资源
            cargo = 0;
        }
    }

    int  value = -99;
    void read_value() {
        std::cin >> value;
        cv.notify_one();
    }
};

thread_wait::thread_wait() {}

thread_wait::~thread_wait() {}

#endif