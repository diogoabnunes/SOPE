#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define MAX_LEN 512
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

struct req_ans {
    struct request *req;
    struct answer *ans;
};

int init_fifo(char *path, int perms);

void *sum(void *arg) {
    struct req_ans *req_ans = (struct req_ans *)arg;
    req_ans->ans->sum = req_ans->req->numbers[0] + req_ans->req->numbers[1];
    pthread_exit(NULL);
}

void *diff(void *arg) {
    struct req_ans *req_ans = (struct req_ans *)arg;
    req_ans->ans->diff = req_ans->req->numbers[0] - req_ans->req->numbers[1];
    pthread_exit(NULL);
}

void *mult(void *arg) {
    struct req_ans *req_ans = (struct req_ans *)arg;
    req_ans->ans->mult = req_ans->req->numbers[0] * req_ans->req->numbers[1];
    pthread_exit(NULL);
}

void *divi(void *arg) {
    struct req_ans *req_ans = (struct req_ans *)arg;

    if (req_ans->req->numbers[1] == 0) {
        req_ans->ans->invalid = 1;
        req_ans->ans->divi = 0;
    }
    else {
        req_ans->ans->divi = (float)req_ans->req->numbers[0] / req_ans->req->numbers[1];
        req_ans->ans->invalid = 0;
    }
    pthread_exit(NULL);
} 

int main()
{
    struct request req;
    struct answer ans;

    unlink(REQUEST_FIFO);
    int fd_req = init_fifo(REQUEST_FIFO, 0660);
    read(fd_req, &req, sizeof(req));

    int fd_ans = open(req.name, O_WRONLY);
    if (fd_ans == -1) {
        printf("The server is now closed!\n");
        close(fd_req);
        unlink(req.name);
        exit(1);
    }
    else close(fd_req);

    struct req_ans req_ans = {&req, &ans};

    pthread_t tidSum, tidDiff, tidMult, tidDivi;
    pthread_create(&tidSum, NULL, sum, &req_ans);
    pthread_create(&tidDiff, NULL, diff, &req_ans);
    pthread_create(&tidMult, NULL, mult, &req_ans);
    pthread_create(&tidDivi, NULL, divi, &req_ans);
    pthread_join(tidSum, NULL);
    pthread_join(tidDiff, NULL);
    pthread_join(tidMult, NULL);
    pthread_join(tidDivi, NULL);

    write(fd_ans, &ans.sum, sizeof(ans.sum));
    write(fd_ans, &ans.diff, sizeof(ans.diff));
    write(fd_ans, &ans.mult, sizeof(ans.mult));
    write(fd_ans, &ans.divi, sizeof(ans.divi));
    write(fd_ans, &ans.invalid, sizeof(ans.invalid));

    close(fd_ans);
    close(fd_req);
    unlink(REQUEST_FIFO);
    unlink(req.name);
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

    if ((fd = open(path, O_RDONLY)) != -1)
        printf("FIFO '%s' openned in READONLY mode\n", path);
    else
    {
        perror("Could not open FIFO");
        exit(2);
    }

    return fd;
}