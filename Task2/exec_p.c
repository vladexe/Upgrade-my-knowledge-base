#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){

    int fork_id;

    fork_id = fork();
    if(fork_id == -1){
        perror("fork error");
        return 1;
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
    return (0);
}