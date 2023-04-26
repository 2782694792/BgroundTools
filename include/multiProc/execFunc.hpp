#ifndef MULTIPROC_EXECFUNC_H
#define MULTIPROC_EXECFUNC_H

#include <stdio.h>
#include <unistd.h> // 使用fork,exec函数
#include <sys/wait.h> // 使用waitpid
#include <stdlib.h> // 使用exit的头文件

class exec_func {
public:
    void main_execlp_ls() // 执行已有可执行程序 ls
    {
        pid_t pid;

        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0) {
            execlp("ls", "ls", "-la", NULL); // 
        }
        else if (pid > 0) {
            sleep(1);
            printf("Finish : execlp 执行已有可执行程序 ls！\n");
        }
    }

    void main_execlp_inheritEnv() { // 继承 shell 进程的所有环境变量
        if (fork() == 0) {
            if (execlp("/usr/bin/env", "env", NULL) < 0) {
                perror("execlp error!");
            }
        }
    }

    void main_execl_multiProc() {
        pid_t pid;

        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0) {
            printf("subprocess start!");
            execl("./bin/BgTools_multiProc", "./bin/BgTools_multiProc", NULL);
            printf("subprocess end!\n");
        }
        else if (pid > 0) {
            sleep(1);
            printf("parent end!\n");
        }
    }

    void main_execv_ls() {
        if (fork() == 0) {
            char* const argv[] = { "ls", "-a", "-l", NULL };
            execv("/usr/bin/ls", argv);
            execvp("ls", argv);
            exit(1);
        }
        int waitRet = waitpid(-1, NULL, 0); // 阻塞等待所有子进程结束
        if (waitRet < 0) {
            perror("wait error\n");
        }
        printf("parent wait child success\n");
    }

};

#endif
