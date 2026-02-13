#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

void signal_handler(int signal) {
    if(signal == SIGUSR1) {
        printf("Child says hello! \n");
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork");
        return 1;
    }

    if(pid == 0) {
        sleep(3);
        kill(getppid(), SIGUSR1);
        exit(0);
    } else {
        printf("Parent waiting for signal... \n");
        pause();
    }

    return 0;
}
