#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

void signal_handler(int signal) {
    
    if(signal == SIGUSR1) {
        printf("Parent says hello! \n");
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
            perror("signal");
            return 1;
        }

        printf("Child: i'm waiting signal from parent...\n");

        pause();
    } 
    else {
        // Parent 
        printf("Parent: waiting 5 sec...\n");
        sleep(5);

        printf("Parent: send SIGUSR1 signal to child\n");
        kill(pid, SIGUSR1);

        wait(NULL);
    }

    return 0;
}
