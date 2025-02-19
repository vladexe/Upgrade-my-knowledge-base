#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void){

    int f1_pid, f2_pid, fd[2];

    if(pipe(fd) == -1){
        perror("pipe error");
        return 1;
    }
    f1_pid = fork();
    if(f1_pid == -1){
        perror("fork error");
        exit(3);
    }
    if(f1_pid == 0){ // pind child process
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
        perror("execlp ping error");
        exit(3);
    }
    f2_pid = fork();
    if(f2_pid == -1){
        perror("fork error");
        exit(3);
    }
    if(f2_pid == 0){ // grep child process
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp("grep", "grep", "rtt", NULL);
        perror("execlp grep error");
        exit(3);
    }
    close(fd[0]);
    close(fd[1]);
    if(waitpid(f1_pid, NULL, 0) == -1){
        perror("waitpid 1 error");
        return 4;
    }
    if(waitpid(f2_pid, NULL, 0) == -1){
        perror("waitpid 2 error");
        return 5;
    }

    return (0);
}