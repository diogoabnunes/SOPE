#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;
int status;

void sig_handler(int signo) {
    pid = wait(&status);
    if (pid != -1)
        printf("PARENT: child with PID=%d terminated with exit code %d\n", pid, WEXITSTATUS(status));
}

int main()
{
    struct sigaction action;
    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGCHLD, &action, NULL);

    int i, n;

    for (i = 1; i <= 10; i++) {
        pid = fork();

        if (pid == 0) {
            printf("CHILD no. %d (PID=%d) working ...\n", i, getpid());
            sleep(5);
            printf("CHILD no. %d (PID=%d) exiting ...\n", i, getpid());
            exit(0);
        }
    }

    for (i = 1; i <= 4; i++) {
        printf("PARENT: working hard (task no. %d) ...\n", i);
        n = 20;
        while ((n = sleep(n)) != 0);
        printf("PARENT: end of task no. %d\n", i);
    }
    
    exit(0);
}