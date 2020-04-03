#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int main() {
    int fd[2];
    pid_t pid;

    pipe(fd);
    pid = fork();

    if (pid > 0){ // pai -> ler 2 ints
        int a[2];
        printf("PARENT\n");
        printf("x y ? ");
        scanf("%d %d", &a[0], &a[1]);
        close(fd[READ]);
        write(fd[WRITE], a, 2*sizeof(int));
        close(fd[WRITE]);
    }
    else { // filho -> realizar a operação
        int b[2];
        close(fd[WRITE]);
        read(fd[READ], b, 2*sizeof(int));
        printf("SON\n");
        printf("x + y = %d\n", b[0] + b[1]);
        printf("x - y = %d\n", b[0] - b[1]);
        printf("x * y = %d\n", b[0] * b[1]);
        if (b[1] != 0) printf("x / y = %f\n", b[0] / (float)b[1]);
        else printf("Denominator cannot be zero. / invalid.\n");
        close(fd[READ]);
    }
    return 0;
}