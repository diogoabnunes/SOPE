#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2

int n = 50000;

void* thrfunc(void* arg) {
    int* numChars = malloc(sizeof(int));
    *numChars = 0;

    fprintf(stderr, "Starting thread %s\n", (char*) arg);
    
    while (n > 0) {
        n--;
        ++(*numChars);

        write(STDERR, arg, 1);
    }

    return numChars;
}

int main() {
    pthread_t ta, tb;

    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");

    void* taReturn;
    void* tbReturn;

    pthread_join(ta, &taReturn);
    pthread_join(tb, &tbReturn);

    int numChars = *((int*) taReturn) + *((int*) tbReturn);
    free(taReturn);
    free(tbReturn);

    fprintf(stderr, "\nTotal chars written: %d\n", numChars);

    return 0;
}