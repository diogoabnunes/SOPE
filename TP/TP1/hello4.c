#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int count = atoi(argv[2]);
    while (count > 0)
    {
        printf("Hello %s !\n", argv[1]);
        count--;
    }
    return 0;
}