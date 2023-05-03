#include "multi_thread/join.hpp"
#include "multi_thread/mutex.hpp"

static const int MAX = 1e8;

int main(int argc, char const *argv[])
{
    thread_join a;
    a.threadjoin();

    thread_mutex b;
    b.concurrent_task(1, MAX);
    
    return 0;
}
