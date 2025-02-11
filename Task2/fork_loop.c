#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

#define PROCESS_NUM 5

int main(void){

    int i = 0;
    // Save the parent PID to ensure the final message is printed by the parent
    pid_t x = getpid();

    for(i; i < PROCESS_NUM; i++){
        if (fork() == 0 ){
            printf("Hello from process %d my parrent is %d\n", getpid(), getppid());
            // We need to exit the child process immediately, or it will also fork,
            // leading to exponentially growing processes (fork bomb).
            exit(0);
        }
            
    }

    // The parent waits for all child processes to finish.
    // Without this loop, finished child processes would become zombies.
    for(i = 0; i < PROCESS_NUM; i++)
        wait(NULL);
    
    // If we are still in the original parent process, print the final message.
    pid_t y = getpid();
    if (x == y)
        printf("\nMain process finished work\n");
    return(0);
}