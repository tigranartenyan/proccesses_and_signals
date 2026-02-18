#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid1 = fork();
    
    if(pid1 < 0) {
        perror("First fork error");
        return 1;
    } 
    
    if(pid1 == 0) {
        char* args[] = {"date", NULL};
        execv("/usr/bin/date", args);
        
        perror("First child execv() error");
        _exit(1);
    }
    
    if(pid1 > 0) {
        pid_t pid2 = fork();
        if(pid2 < 0) {
            perror("Second fork error");
            return 1;
        }
    
        if(pid2 == 0) {
            char* args[] = {"whoami", NULL};
            execv("/usr/bin/whoami", args);
    
            perror("Second child execv() error");
            _exit(1);
        }
    
    
        int status;
        pid_t whoFirst = wait(&status);
    
        if(whoFirst < 0) {
            perror("Error while waiting first child...");
            return 1;
        }
    
        if(whoFirst == pid1) {
            printf("The first child (date) completed first! \n");
        } else if(whoFirst == pid2) {
            printf("The second child (whoami) completed first! \n");
        } else {
            printf("The undefined child completed first... \n");
        }

        if(wait(NULL) < 0) {
            perror("Error while second child waiting...");
            return 1;
        }
    }
    
    return 0;
}
