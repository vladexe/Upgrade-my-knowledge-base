#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void){

    int fork_id, output_fd, error_fd;

    output_fd = open("logs.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(output_fd == -1){
        perror("open error");
        return 1;
    }
    // All standard output are redirected to the file logs.txt
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
    error_fd = open("error.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(error_fd == -1){
        perror("open error");
        return 1;
    }
    // All errors are redirected to the errors.txt
    dup2(error_fd, STDERR_FILENO);
    close(error_fd);
    fork_id = fork();
    if(fork_id == -1){
        perror("fork error");
        return 2;
    }
    if(fork_id == 0){ // Child
        char *arg[] = {"whoami", NULL};
        // p - means that path will be checking in PATH
        if(execvp("whoami", arg)){
            perror("execlp error");
            exit(3);
        }
    } else{ // Parent
        // p - means that path will be checking in PATH
        // we need to wait until execlp is called
        wait(NULL);
        if(execlp("pwd", "pwd", NULL)){
            perror("parent execlp error");
            exit(3);
        }
    }
    return(0);
}