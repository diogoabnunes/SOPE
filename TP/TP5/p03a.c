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

        int bytesRead;
        char buf[512];

        while ((bytesRead = read(fd, buf, 512)) > 0) {
            write(pipeFD[WRITE], buf, bytesRead);
        }

        close(pipeFD[WRITE]);
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