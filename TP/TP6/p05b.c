#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float a, b;
} Nums;

void* add(void* args)
{
    float* result = malloc(sizeof(float));
    *result = (*(Nums*)args).a + (*(Nums*)args).b;
    pthread_exit(result);
}

void* diff(void* args)
{
    float* result = malloc(sizeof(float));
    *result = (*(Nums*)args).a - (*(Nums*)args).b;
    pthread_exit(result);
}

void* mult(void* args)
{
    float* result = malloc(sizeof(float));
    *result = (*(Nums*)args).a * (*(Nums*)args).b;
    pthread_exit(result);
}

void* divi(void* args)
{
    float* result = malloc(sizeof(float));
    *result = (*(Nums*)args).a / (*(Nums*)args).b;
    pthread_exit(result);
}

int main()
{
    pthread_t threads[4];
    Nums numbers;
    
    printf("Numbers a b: ");
    scanf("%f %f", &numbers.a, &numbers.b);

    for (int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0: pthread_create(&threads[0], NULL, add, &numbers); break;
            case 1: pthread_create(&threads[1], NULL, diff, &numbers); break;
            case 2: pthread_create(&threads[2], NULL, mult, &numbers); break;
            case 3: pthread_create(&threads[3], NULL, divi, &numbers); break;
        }
    }

    char *opers[4] = {"Sum", "Diff", "Mult", "Divi"};
    void *returnValue;

    for (int i = 0;i < 4; i++)
    {
        pthread_join(threads[i], &returnValue);

        printf("%s: %f\n", opers[i], *(float*)returnValue);
    }

    pthread_exit(0);
}