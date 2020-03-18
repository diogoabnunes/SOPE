#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2 && argc != 3) {
        printf("usage: %s dirname [textfile output]\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0) {
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
    }
    else if (pid == 0) {
        if (argc == 3) {
            int file = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644);

            if (file == -1) {
                printf("%s already exists", argv[2]);
                exit(2);
            }

            if (dup2(file, STDOUT_FILENO) == -1) {
                printf("Error");
                exit(3);
            }
        }

        write(STDOUT_FILENO, "Copying output", 14);
        execlp("ls", "ls", "-laR", argv[1], NULL);

        printf("Command not executed!\n");
        exit(1);
    }
    exit(0);
}