#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// pai: "world !"
// filho: "Hello "
int main() {
    pid_t pid, pid2;
    pid = fork();

    if (pid > 0) {
        printf("Hello ");
    }
    else if (pid == 0) {
        pid2 = fork();
        
        if (pid2 > 0) {
            printf("my ");
        }
        else if (pid2 == 0) {
            printf("friends!\n");
        }
    }
    
    return 0;
}