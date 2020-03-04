#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 512

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

    char name[BUFFER_SIZE];
    int score;
    char outbuf[BUFFER_SIZE+6];

    while (scanf("%s %d", name, &score) > 0)
    {
        sprintf(outbuf, "%s %d", name, score);
        write(output_file, outbuf, (strlen(outbuf))*sizeof(*outbuf));
        write(output_file, "\n", 1);
    }

    close(output_file);
    return 0;
}
