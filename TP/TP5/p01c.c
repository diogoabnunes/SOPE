#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int main() {
    int fd[2];
    pid_t pid;

    pipe(fd);
    pid = fork();

    if (pid > 0) { // pai -> ler 2 ints
        char a[2][10];
        printf("PARENT\n");
        printf("x y ? ");
        scanf("%s %s", a[0], a[1]);
        close(fd[READ]);
        write(fd[WRITE], a, 2*sizeof(char)*10);
        close(fd[WRITE]);
    }
    else { // filho -> realizar a operação
        char b[2][10];
        close(fd[WRITE]);
        read(fd[READ], b, 2*sizeof(char)*10);
        printf("SON\n");
        printf("x + y = %d\n", atoi(b[0]) + atoi(b[1]));
        printf("x - y = %d\n", atoi(b[0]) - atoi(b[1]));
        printf("x * y = %d\n", atoi(b[0]) * atoi(b[1]));
        if (atoi(b[1]) != 0) printf("x / y = %f\n", atoi(b[0]) / (float)atoi(b[1]));
        else printf("Denominator cannot be zero. / invalid.\n");
        close(fd[READ]);
    }
    return 0;
}