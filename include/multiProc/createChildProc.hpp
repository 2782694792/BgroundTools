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

    int main_createChildProc() {
        pid_t pid;
        printf("xxxxxxxxxxxxx\n");
        pid = fork(); // one call, two return
        if (pid == -1) {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0) { // 子进程
            printf("I'm child, pid = %u, ppid = %u\n", getpid(), getppid());
        }
        else {
            printf("I'm parent, pid = %u, ppid = %u\n", getpid(), getppid());
            sleep(1);
        }
        printf("yyyyyyyyyyyyyy\n");
    }
};


#endif