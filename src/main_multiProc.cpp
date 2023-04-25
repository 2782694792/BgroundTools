#include <stdio.h>
#include <unistd.h>
// #include <stdlib.h>

int main()
{
    pid_t pid;
    printf("xxxxxxxxxxxxx\n");
    pid = fork(); //one call, two return
    if (pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0)
    { //子进程
        printf("I'm child, pid = %u, ppid = %u\n", getpid(), getppid());
    }
    else
    {
        printf("I'm parent, pid = %u, ppid = %u\n", getpid(), getppid());
        sleep(1);
    }
    printf("yyyyyyyyyyyyyy\n");
    return 0;
}

