#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int v = 0;

void sigusr_handler(int signo)
{
    if (signo == SIGUSR1) v++;
    else if (signo == SIGUSR2) v--;
}

int main()
{
    srand(time(0));
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Error fork\n");
        exit(1);
    }
    if (pid == 0) {
        struct sigaction action;
        action.sa_handler = sigusr_handler;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0;

        if (sigaction(SIGUSR1, &action, NULL) < 0) {
            fprintf(stderr, "Unable to install SIGUSR1 handler\n");
            exit(2);
        }
        else if (sigaction(SIGUSR2, &action, NULL) < 0) {
            fprintf(stderr, "Unable to install SIGUSR2 handler\n");
            exit(2);
        }

        for (;;) {
            sleep(1);
            printf("v: %d\n", v);
        }
    }
    else {
        printf("Parent process\n");
        int i = 50;
        while (i > 0) {
            (rand() % 2 == 0) ? kill(pid, SIGUSR1) : kill(pid, SIGUSR2);
            sleep(1);
            i--;
        }
        kill(pid, SIGTERM);
    }
    return 0;
}