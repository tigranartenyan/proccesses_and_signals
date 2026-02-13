#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("Caught Ctrl+C\n");
    } else if (sig == SIGTSTP) {
        printf("Caught Ctrl+Z\n");
    } else if (sig == SIGQUIT) {
        printf("Caught Ctrl+\\\n");
        printf("End of program! \n");
        exit(0); 
    }
}

int main(void) {
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal SIGINT");
        return 1;
    }
    if (signal(SIGTSTP, signal_handler) == SIG_ERR) {
        perror("signal SIGTSTP");
        return 1;
    }
    if (signal(SIGQUIT, signal_handler) == SIG_ERR) {
        perror("signal SIGQUIT");
        return 1;
    }

    printf("Program started.\n");
    printf("Enter Ctrl+C, Ctrl+Z or Ctrl+\\ \n");

    while (1) {
        pause(); 
    }

    return 0;
}