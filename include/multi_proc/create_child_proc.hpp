#ifndef MULTIPROC_CREATECHILD_H
#define MULTIPROC_CREATECHILD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class createChildProc {
private:
public:
    createChildProc() {}
    ~createChildProc() {}

    void main_crtOnce() {
        int   count = 0;
        pid_t pid;
        printf("Start : main create once\n");
        pid = fork(); // one call, two return
        if (pid == -1) {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0) { // subprocess
            count = 11;
            printf("child, count = %d, pid = %u, ppid = %u\n", count, getpid(),
                   getppid());
        }
        else { // parent process
            count = 22;
            printf("parent, count = %d, pid = %u, ppid = %u\n", count, getpid(),
                   getppid());
            sleep(1);
        }

        printf("Finish : create once, count = %d!\n", count);
    }

    void main_crtMore() {
        int   i = 0;
        pid_t pid;
        for (i = 0; i < 5; i++) {
            pid = fork();
            if (pid == -1) {
                perror("fork error");
                exit(1);
            }
            else if (pid == 0) { // 子进程
                break;
            }
        }
        if (i < 5) {
            sleep(i);
            printf("I'm %dth child, pid = %u, ppid = %u\n", i + 1, getpid(),
                   getppid());
        }
        else {
            sleep(i);
            printf("I'm parent, pid = %u, ppid = %u\n", getpid(), getppid());
        }
    }

    void main_countMore() {
        int i = 0;
        printf("i son/pa ppid pid fpid\n");
        // ppid指当前进程的父进程pid
        // pid指当前进程的pid,
        // fpid指fork返回给当前进程的值
        for (i = 0; i < 2; i++) {
            pid_t fpid = fork();
            if (fpid == 0)
                printf("%d child %4d %4d %4d\n", i, getppid(), getpid(), fpid);
            else
                printf("%d parent %4d %4d %4d\n", i, getppid(), getpid(), fpid);
        }
    }
};


#endif