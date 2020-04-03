#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

struct values {
    int a;
    int b;
};

int main() {
    int fd[2];
    pid_t pid;

    pipe(fd);
    pid = fork();

    if (pid > 0){ // pai -> ler 2 ints
        struct values aval;
        printf("PARENT\n");
        printf("x y ? ");
        scanf("%d %d", &aval.a, &aval.b);
        close(fd[READ]);
        write(fd[WRITE], &aval, 2*sizeof(int));
        close(fd[WRITE]);
    }
    else { // filho -> realizar a operação
        struct values bval;
        close(fd[WRITE]);
        read(fd[READ], &bval, 2*sizeof(int));
        printf("SON\n");
        printf("x + y = %d\n", bval.a + bval.b);
        printf("x - y = %d\n", bval.a - bval.b);
        printf("x * y = %d\n", bval.a * bval.b);
        if (bval.b != 0) printf("x / y = %f\n", bval.a / (float)bval.b);
        else printf("Denominator cannot be zero. / invalid.\n");
        close(fd[READ]);
    }
    return 0;
}