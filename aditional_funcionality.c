void SIGINT_handler(int signo) {
  char quit;
  regSendSignal(getppid(), SIGSTOP);

  while (1) {
    printf("Are you sure you want to quit?\nY: Yes, I want to quit\nN: No, I want to continue\n");
    scanf("%s", &quit);

    if (quit == 'N' || quit == 'n') {
      regSendSignal(getppid(), SIGCONT);
      return;
    }
    else if (quit == 'Y' || quit == 'y') {
      regSendSignal(getppid(), SIGQUIT);
      regSendSignal(getpid(), SIGQUIT);
      return;
    }
    else continue;
  }
}

void SIGINT_subscriber() {
  struct sigaction action;
  action.sa_handler = SIGINT_handler;
  action.sa_flags = 0;
  sigemptyset(&action.sa_mask);
  sigaction(SIGINT, &action, NULL);
}
