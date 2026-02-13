#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0;

void signal_handler() {

    count++;
    printf("SIGQUIT working...\n");

    if(count >= 3) {
        printf("SIGQUIT was called 3 times, end of program... \n");
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    if (signal(SIGQUIT, signal_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    printf("The program runned. Enter Ctrl+\\ (SIGQUIT).\n");

    while (1) {
        pause(); 
    }
    return 0;
}
