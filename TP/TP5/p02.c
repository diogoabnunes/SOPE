#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#define READ 0
#define WRITE 1

struct results {
    int sum; int dif; int prod; float div; bool invalid;
};

int main() {
    int fd1[2], fd2[2];
    pid_t pid;

    pipe(fd1);
    pipe(fd2);
    pid = fork();

    if (pid > 0){ // pai -> ler 2 ints
        int a[2];
        struct results values1;
        printf("PARENT\n");
        printf("x y ? ");
        scanf("%d %d", &a[0], &a[1]);
        close(fd1[READ]);
        close(fd2[WRITE]);
        write(fd1[WRITE], a, 2*sizeof(int));
        close(fd1[WRITE]);

        read(fd2[READ], &values1, sizeof(float)*4);
        printf("x + y = %d\n", values1.sum);
        printf("x - y = %d\n", values1.dif);
        printf("x * y = %d\n", values1.prod);
        if (values1.invalid) printf("Denominator cannot be zero. / invalid.\n");
        else printf("x / y = %f\n", values1.div);

    }
    else { // filho -> realizar a operação
        int b[2];
        struct results values2; values2.invalid = false;
        close(fd1[WRITE]);
        read(fd1[READ], b, 2*sizeof(int));

        printf("SON\n");
        values2.sum = b[0] + b[1];
        values2.dif = b[0] - b[1];
        values2.prod = b[0] * b[1];
        if (b[1] != 0) values2.div = b[0] / (float)b[1];
        else values2.invalid = true;
        close(fd1[READ]);
        write(fd2[WRITE], &values2, sizeof(float)*4);
    }
    return 0;
}