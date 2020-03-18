#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2) {
        printf("usage: %s dirname\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0) {
        int child;
        wait(&child);

        printf("Child process return with: %d\n", child);
        
        if (WIFEXITED(child)) {
            printf("Child process finished\n");
        }
        else if (WIFSIGNALED(child)) {
            printf("Signaled process\n");
        }
    }
    else if (pid == 0) {
        execlp("ls", "ls", "-laR", argv[1], NULL);
        printf("Command not executed!\n");
        exit(1);
    }
    exit(0);
}