#ifndef MULTIPROC_WAIT_HPP
#define MULTIPROC_WAIT_HPP

#include <stdio.h>
#include <unistd.h> // 使用fork,exec函数
#include <stdlib.h> // 使用exit的头文件
#include <sys/wait.h> // 使用waitpid

class wait_func
{    
public:
    wait_func() {}
    ~wait_func() {}

    
    void main_wait() {
        pid_t pid, wpid;
        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0) { // 子进程
            printf("child, pid = %d, ppid = %d, sleep 3s\n", getpid(),
                   getppid());
            sleep(3);
            printf("******child die!*******\n");
            exit(9);
        }
        else if (pid > 0) {    // 父进程
            // wpid = wait(NULL); // 阻塞 等待回收
            int status;
            wpid = wait(&status); // 阻塞，回收状态信息
            if (wpid == -1) {
                perror("wait error");
                exit(1);
            }

            if (WIFEXITED(status))
            { 
                printf("child exit with  %d\n", WEXITSTATUS(status));
            }

            if (WIFSIGNALED(status))
            { //信号终止
                printf("child killed by %d\n", WTERMSIG(status));
            }
            printf("parent end! pid = %d\n", getpid());
        }
    }

    void main_waitpid() {
        pid_t pc, pr;
        pc = fork();
        if (pc < 0) /* 如果fork出错 */
        {
            printf("Error occured on forking.\n");
        }
        else if (pc == 0) /* 如果是子进程 */
        {
            sleep(10); /* 睡眠10秒 */
            exit(0);
        }

        /* 如果是父进程 */
        do {
            pr =
                waitpid(pc, NULL,
                        WNOHANG); /* 使用了WNOHANG参数，waitpid不会在这里等待 */
            if (pr == 0) /* 如果没有收集到子进程 */
            {
                printf("No child exited\n");
                sleep(1);
            }
        } while (pr == 0); /* 没有收集到子进程，就回去继续尝试 */

        if (pr == pc) {
            printf("successfully get child %d\n", pr);
        }
        else
            printf("some error occured\n");
    }

};


#endif