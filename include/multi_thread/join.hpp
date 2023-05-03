#ifndef MULTI_THREAD_JOIN_H
#define MULTI_THREAD_JOIN_H

#include <iostream>
#include <thread>
#include <string>

class thread_join {
public:
    thread_join() {}
    ~thread_join() {}

    void hello() {
        std::cout << "hello world" << std::endl;
    }

    void world(const std::string & name) {
        std::cout << name << std::endl;
    }

    void threadjoin() {
        std::thread t(&thread_join::hello, this); // 创建一个thread对象，并指定入口函数。
        t.join();
        std::thread t2([](){ std::cout << "hello world lambda" << std::endl; });
        t2.join();
        std::string temp = "transfer parameter";
        std::thread t3(&thread_join::world, this, std::ref(temp)); // 传递参数 拷贝传参
        t3.join();
    }
};


#endif