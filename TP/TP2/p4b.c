#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 512

typedef struct
{
    char name[50];
    int score;
} Student;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Wrong no. of arguments.\nUsage: %s <file to write>\n", argv[0]);
        return 1;
    }

    int output_file = open(argv[1], O_WRONLY | O_CREAT, 0644);
    if (output_file == -1) {
        perror(argv[1]);
        return 2;
    }

    printf("<name> <score>\nEOF to exit.\n");

    Student bro;

    while (scanf("%s %d", bro.name, &(bro.score)) > 0)
    {
        write(output_file, &bro, sizeof(bro));
    }

    close(output_file);
    return 0;
}
