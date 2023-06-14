#ifndef MULTI_LOCK_JOIN_H
#define MULTI_LOCK_JOIN_H

#include <iostream>
#include <mutex>
#include <thread>

struct Box {
    explicit Box(int num) : num_things{ num } {}
    int        num_things;
    std::mutex m;
};

class thread_lock {
public:
    thread_lock();
    ~thread_lock();

    void transfer(Box& from, Box& to, int num) {
        // defer_lock表示暂时unlock，默认自动加锁
        std::unique_lock< std::mutex > lock1(from.m, std::defer_lock);
        std::unique_lock< std::mutex > lock2(to.m,
                                             std::defer_lock); // 两个同时加锁
        std::lock(lock1, lock2); // 或者使用lock1.lock()

        from.num_things -= num;
        to.num_things +=
            num; // 作用域结束自动解锁,也可以使用lock1.unlock()手动解锁
    }
};

thread_lock::thread_lock() {}

thread_lock::~thread_lock() {}


#endif