#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_LEN 512
#define ANSWER_FIFO "/tmp/fifo_ans"
#define REQUEST_FIFO "/tmp/fifo_req"

struct request {
    int numbers[2];
    char name[MAX_LEN];
};

struct answer {
    int sum, diff, mult;
    float divi;
    int invalid;
};

int init_fifo(char *path, int perms);

int main()
{
    char fifo_ans[MAX_LEN];
    int pid = getpid();
    sprintf(fifo_ans, "%s_%d", ANSWER_FIFO, pid);
    int fd_ans = init_fifo(fifo_ans, 0660);

    int fd_req = open(REQUEST_FIFO, O_WRONLY);
    if (fd_req == -1)
    {
        printf("The server is now closed!\n");
        close(fd_req);
        unlink(fifo_ans);
        exit(1);
    }
    else
    {
        close(fd_ans);
    }

    struct request req;
    strcpy(req.name, fifo_ans);
    printf("Numbers: ");
    scanf("%d %d", &req.numbers[0], &req.numbers[1]);
    write(fd_req, &req, sizeof(req));
    
    struct answer ans;
    fd_ans = open(fifo_ans, O_RDONLY);
    read(fd_ans, &ans.sum, sizeof(ans.sum));
    read(fd_ans, &ans.diff, sizeof(ans.diff));
    read(fd_ans, &ans.mult, sizeof(ans.mult));
    read(fd_ans, &ans.divi, sizeof(ans.divi));
    read(fd_ans, &ans.invalid, sizeof(ans.invalid));

    printf("Sum: %d\n", ans.sum);
    printf("Diff: %d\n", ans.diff);
    printf("Mult: %d\n", ans.mult);
    if (ans.invalid == 1) printf("Divi invalid (denominator = 0)\n");
    else printf("Divi: %f\n", ans.divi);

    close(fd_req);
    close(fd_ans);
    unlink(ANSWER_FIFO);
    exit(0);
}

int init_fifo(char *path, int perms)
{
    if (mkfifo(path, perms) < 0)
    {
        perror("Can't create FIFO");
        exit(1);
    }
    else
    {
        printf("FIFO '%s' sucessfully created\n", path);
    }

    int fd;

    if ((fd = open(path, O_RDONLY | O_NONBLOCK)) != -1)
        printf("FIFO '%s' openned in READONLY mode\n", path);
    else
    {
        perror("Could not open FIFO");
        exit(2);
    }

    return fd;
}