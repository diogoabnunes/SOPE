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

    int input_file = open(argv[1], O_RDONLY);
    if (input_file == -1) {
        perror(argv[1]);
        return 2;
    }

    Student bro;

    while (read(input_file, &bro, sizeof(bro)) > 0)
    {
        printf("Name: %s Score: %d\n", bro.name, bro.score);
    }

    close(input_file);
    return 0;
}
