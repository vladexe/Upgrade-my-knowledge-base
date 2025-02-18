#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main(void){

    srand(time(NULL));
    int fork_id, random = rand() % 2;

    printf("Random choose %d\n", random);
    

    fork_id = fork();
    if(fork_id == -1){
        perror("fork issue");
    }
    if(fork_id == 0){ // Child process
        if(random == 0){
            // execl - arguments passed as separate parameters	
            puts("We will test EXECL");
            if(execl("/usr/bin/ping", "ping", "-c", "8", "google.com", NULL)){
                perror("execl error");
                exit(3);
            }
        } else if(random == 1){
            // execv - arguments passed as array
            puts("We will test EXECV");
            char *arg[] = {"ping", "-c", "3", "google.com", NULL};
            if(execv("/usr/bin/ping", arg)){
                perror("execl error");
                exit(3);
            }
        }
        // next code should be not executed because exec family of command 
        // replacing actual program with the passing one to the arguments
        puts("This text should be not displayed on the terminal");
    } else{
        puts("So we are in the parrent process");
        // We could wait before child process finished
        wait(NULL);
    }
    return (0);
}