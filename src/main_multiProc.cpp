#include "multiProc/createChildProc.hpp"
#include "multiProc/execFunc.hpp"
#include <stdlib.h>

int main()
{
    createChildProc a;
    // a.main_crtOnce(); // 单个子进程
    // a.main_crtMore(); // 多个子进程
    // a.main_countMore(); // 计算进程数

    exec_func b;
    // b.main_execlp_ls(); // 执行目录下已有可执行文件 ls
    // b.main_execlp_inheritEnv(); // 继承 shell 进程的所有环境变量
    b.main_execl_multiProc(); // 执行自定义程序 multiProc

    return EXIT_SUCCESS;
}

