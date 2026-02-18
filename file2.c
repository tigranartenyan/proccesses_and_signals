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
        execlp("sleep", "sleep", "3", NULL);

        perror("execlp()");
        _exit(1);
    }

    if(pid > 0) {
        printf("Waiting for child proccess \n");
    }
    
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return 1;
    }

    if (pid > 0) {
        waitpid(pid, &status, 0);
        printf("End waiting\n");
    }

    if(WIFEXITED(status)) {
        printf("The proccess was ended at %d code! \n", WEXITSTATUS(status));
    } 
    else if(WIFSIGNALED(status)) {
        printf("The proccess was ended because signal: %d\n", WTERMSIG(status));
    }

    return 0;
}
