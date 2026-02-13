#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char const *argv[])
{

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork error");
        return 1;
    } 
    
    if(pid == 0) {
        int fd = open(file2, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if(fd < 0) {
            perror("Can't open second file");
            _exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);

        execl("/usr/bin/cat", "cat", file1, NULL);
        _exit(1);
    }

    wait(NULL);



    return 0;
}
