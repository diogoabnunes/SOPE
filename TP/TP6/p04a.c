#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

void* threadFunc(void* arg) {
    pthread_t tid = pthread_self();
    sleep(1);
    printf("%lu\n", (unsigned long) tid);
    printf("Thread %d returned %d.\n", *(int*)arg, *(int*)arg);
    pthread_exit(arg);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadNums[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        threadNums[i] = i + 1;
        
        pthread_create(&threads[i], NULL, threadFunc, &threadNums[i]);
    }

    void* returnValue;

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], &returnValue);
    }

    pthread_exit(0);
}