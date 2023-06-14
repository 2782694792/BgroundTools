#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <assert.h>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory> //unique_ptr
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

// const int MAX_THREADS = 1000; // 最大线程数目
const int MAX_THREADS = std::thread::hardware_concurrency(); // 最大线程数目
// using task_t = std::function< void() >;

template < typename T > class threadPool {
public:
    threadPool(int number); // 默认开一个线程
    ~threadPool();

    std::queue< T* > tasks_queue; // 任务队列，先进先出

    bool append(T* request); // 往请求队列＜task_queue＞中添加任务<T>

private:
    // 工作线程需要运行的函数,不断的从任务队列中取出并执行
    static void* worker(void* arg);
    void         run();

private:
    std::vector< std::thread > work_threads; // 工作线程
    std::mutex                 queue_mutex;
    std::condition_variable    condition;    // 与unique_lock配合使用
    bool                       stop;
};

/**
 * @brief  Construct a new thread Pool< T >::thread Pool object
 * @brief
 * 预先创建线程数量，构造时对数量合法性管理，合法则添加到线程池的向量容器中
 * @tparam T 工作任务类
 * @param  number 线程数量
 */
template < typename T >
threadPool< T >::threadPool(int number)
    : stop(false) {
    if (number <= 0 || number > MAX_THREADS)
        throw std::exception();

    for (int i = 0; i < number; i++) {
        std::cout << "created Thread num is : " << i << std::endl;
        work_threads.emplace_back(worker, this);
        // 添加线程, 直接在容器尾部创建这个元素，省去了拷贝或移动。
    }
}

/**
 * @brief  Destroy the thread Pool< T >::thread Pool object
 * @brief  线程全部停止，唤醒线程进行线程阻塞直至完全
 * @tparam T
 */
template < typename T > inline threadPool< T >::~threadPool() {
    std::unique_lock< std::mutex > lock(queue_mutex);
    stop = true;

    condition.notify_all();
    for (auto& ww : work_threads)
        ww.join(); // 可以在析构函数中join
}

/**
 * @brief  添加任务, 添加完成则通知其他线程
 * @tparam T 任务类
 * @param  request 请求的工作任务
 * @return true 添加成功
 * @return false 添加失败
 */
template < typename T > bool threadPool< T >::append(T* request) {
    // 操作工作队列时一定要加锁，因为他被所有线程共享
    queue_mutex.lock(); // 同一个类的锁
    tasks_queue.push(request);
    queue_mutex.unlock();
    condition.notify_one(); // 线程池添加进去了任务，自然要通知等待的线程
    return true;
} // 单个线程

/**
 * @brief  转为工作线程池，同时启动线程池，并返回线程池指针
 * @tparam T
 * @param  arg
 * @return void* 线程池指针
 */
template < typename T > void* threadPool< T >::worker(void* arg) {
    threadPool *pool = ( threadPool* )arg;
    pool->run(); // 线程运行
    return pool;
}

/**
 * @brief
 * @tparam T
 */
template < typename T > void threadPool< T >::run() {
    while (!stop) {
        std::unique_lock< std::mutex > lk(this->queue_mutex);
        /*　unique_lock() 出作用域会自动解锁　*/
        this->condition.wait(lk, [this] {
            return !this->tasks_queue.empty();
        }); // 如果任务为空，则wait，就停下来等待唤醒//需要有任务，才启动该线程，不然就休眠
        if (this->tasks_queue.empty()) // 任务为空，双重保障
        {
            assert(
                0
                && "断了"); // 实际上不会运行到这一步，因为任务为空，wait就休眠了。
            continue;
        }
        else {
            T* request = tasks_queue.front();
            tasks_queue.pop();
            if (request)           // 来任务了，开始执行
                request->process(); 
        }
    }
}

#endif