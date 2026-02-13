#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler() {
    printf("Time's up!\n");
}

int main(int argc, char const *argv[])
{
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("Alarm handler error");
        return 1;
    }

    printf("Waiting 3 sec...\n");

    alarm(3);

    pause();

    printf("The program worked \n");
    return 0;
}