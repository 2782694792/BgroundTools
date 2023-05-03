#include "multi_proc/createChildProc.hpp"
#include "multi_proc/execFunc.hpp"
#include "multi_proc/wait_func.hpp"
#include <stdlib.h>

int main()
{
    createChildProc a;
    // a.main_crtOnce(); // 单个子进程
    // a.main_crtMore(); // 多个子进程
    // a.main_countMore(); // 计算进程数

    // exec_func b;
    // b.main_execlp_ls(); // 执行目录下已有可执行文件 ls
    // b.main_execlp_inheritEnv(); // 继承 shell 进程的所有环境变量
    // b.main_execl_multiProc(); // 执行自定义程序 multiProc

    wait_func c;
    // c.main_wait(); // 阻塞等待回收子进程的销毁
    c.main_waitpid(); // 非阻塞回收子进程的销毁信息

    return EXIT_SUCCESS;
}

