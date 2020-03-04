#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
    for (int i = 0; envp[i] != NULL; i++)
    {
        printf("%s\n", envp[i]);
    }

    printf("\n");

    char *var_USER = "USER=";
    int i = 0;
    for (int i = 0; envp[i] != NULL; i++)
    {
        if (strncmp(var_USER, envp[i], 5) == 0)
        {
            printf("Hello %s !\n", envp[i] + 5);
            break;
        }
    }

    printf("\n");
    
    printf("Hello %s !\n", getenv("USER"));
    printf("Hello %s !\n", getenv("MYNAME"));

    return 0;
}