#include "multi_thread/join.hpp"
#include "multi_thread/lock.hpp"
#include "multi_thread/mutex.hpp"
#include "multi_thread/threadpool.hpp"
#include "multi_thread/wait_waitfor.hpp"

static const int MAX = 1e8;

#include <math.h>
#include <string>
using namespace std;
class Task {
public:
    void process() {
        // cout << "run........." << endl;//测试任务数量
        long i = 1000000;
        while (i != 0) {
            int j = sqrt(i);
            i--;
            std::cout << "j = " << j << std::endl;
        }
    }
};

int main(int argc, char const* argv[]) {
    {
        thread_join a;
        a.threadjoin();
    }
    std::cout << std::endl;

    {
        thread_mutex b;
        b.concurrent_task(1, MAX);
    }
    std::cout << std::endl;

    {
        thread_lock c;
        Box         acc1(100);
        Box         acc2(50);
        std::thread t1(&thread_lock::transfer, &c, std::ref(acc1),
                       std::ref(acc2), 10);
        t1.join();
        std::cout << "acc1 num_things: " << acc1.num_things << std::endl;

        std::thread t2(&thread_lock::transfer, &c, std::ref(acc2),
                       std::ref(acc1), 5);
        t2.join();
        std::cout << "acc2 num_things: " << acc2.num_things << std::endl;
    }
    std::cout << std::endl;

    {
        thread_wait d;
        std::thread consumer_thread(&thread_wait::consume, &d, 10);
        for (int i = 0; i < 10; ++i) {
            // 每次cargo每次为0才运行，线程资源让出，处于就绪状态
            while (d.shipment_available())
                std::this_thread::yield();
            std::unique_lock< std::mutex > lck(d.mtx);
            d.cargo = i + 1;   // 改变线程条件变量
            d.cv.notify_one(); // 唤醒其他线程
        }
        std::cout << "shipment_available" << std::endl;

        consumer_thread.join();
    }
    std::cout << std::endl;

    {
        thread_wait e;
        std::cout << "Please, enter an integer (I'll be printing dots): \n";
        std::thread th(&thread_wait::read_value, &e);

        std::mutex                     mtx;
        std::unique_lock< std::mutex > lck(mtx);
        while (e.cv.wait_for(lck, std::chrono::seconds(1))
               == std::cv_status::timeout) {
            std::cout << '.' << std::endl;
        }
        std::cout << "You entered: " << e.value << '\n';
        th.join();
    }
    std::cout << std::endl;

    {
        threadPool< Task > pool(6); // 6个线程，vector
        std::string        str;

        for (int i = 0; i < 6; i++)        
        {
            Task* tt = new Task(); // 使用智能指针
            pool.append(
                tt); // 不停的添加任务，任务是队列queue，因为只有固定的线程数
            cout << "添加的任务数量：" << pool.tasks_queue.size() << endl;
            delete tt;
        }
    }

    return 0;
}
