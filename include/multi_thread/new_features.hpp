#ifndef MULTI_THREAD_C11_HPP
#define MULTI_THREAD_C11_HPP

#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <functional>

using namespace std;

class new_features {
private:
public:
    new_features();
    ~new_features();

    std::once_flag onceflag;
    void           CallOnce(int index) {
        std::call_once(onceflag,
                                 [index]() { cout << "call_once: " << index << endl; });
    }

    std::atomic< int > count; // 使用原子变量
    void               Atomic() {
        ++count;
        // count.store(++count);这种方式也可以
        cout << "atmoic: " << count << endl;
    }

    void Future(std::future< int >& fut) {
        int x = fut.get(); // 获取线程函数返回值
        cout << "future: " << x << endl;
    }

    void Promise(int value) {
        std::promise< int > prom;                   // 包装值
        std::future< int > fut = prom.get_future(); // 获取与其关联的future对象
        std::thread t(&Future, this, std::ref(fut)); // 提供线程以及线程参数
        prom.set_value(value);                       // 设置包装的值
        t.join();
    }

    int tempfunc(int value) {
        return value + 99;
    }

    void Package_task(int value) {
        std::packaged_task< int(int) > task(std::bind(&new_features::tempfunc, this, std::placeholders::_1));
        std::future< int > fut = task.get_future();
        std::thread taskt(std::move(task), value);
        taskt.detach();
        cout << "packaged_task: " << fut.get() << endl;
    }

    void Async(int value) {
        auto res =
            std::async(std::bind(&new_features::tempfunc, this, value));
        // res.wait();
        cout << "async: " << res.get() << endl; // 阻塞直到函数返回
    }
};

new_features::new_features() {}

new_features::~new_features() {}


#endif