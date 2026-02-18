#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork error");
        return 1;
    }

    if(pid == 0) {
        char* argsArr[] = {"ps", "-e", "-f", NULL};
        execv("/usr/bin/ps", argsArr);

        perror("Execv()");
        _exit(1);
    }

    if(pid > 0) {
        wait(NULL);
    }

    return 0;
}
