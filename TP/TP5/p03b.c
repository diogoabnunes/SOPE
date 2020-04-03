#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    int pipeFD[2]; pipe(pipeFD);
    pid_t pid = fork();

    if (pid > 0) {
        close(pipeFD[READ]);
        dup2(pipeFD[WRITE], STDOUT_FILENO);

        execlp("cat", "cat", argv[1], NULL);
        perror("execlp");
        return 1;
    }
    else {
        close(pipeFD[WRITE]);
        dup2(pipeFD[READ], STDIN_FILENO);

        execlp("sort", "sort", NULL);
        perror("execlp");
        return 1;
    }

    return 0;
}