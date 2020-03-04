#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// pai: "world !"
// filho: "Hello "
int main() {
    pid_t pid, pidSon;
    int status;
    pid = fork();

    if (pid > 0) {
        pidSon = wait(&status);
        printf("world !");
    }
    else if (pid == 0) {
        printf("Hello ");
    }
    
    return 0;
}

// pai: "Hello "
// filho: "world !"
/*
int main() {
    pid_t pid;

    pid = fork();

    if (pid > 0)
        printf("Hello ");
    else if (pid == 0)
        printf("world !\n");

    return 0;
}
*/