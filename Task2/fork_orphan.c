#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

#define PROCESS_NUM 5

int main(void){

    pid_t x = getpid();
    printf("Parrent id is %d\n", x);

    int f_id = fork();

    if(f_id == 0){
        // Before sleep, the child’s parent is still the main process.
        printf("\nWe are in child process %d and our parrent is %d\n", getpid(), getppid());
        sleep(3);
        // After sleep, the original parent has exited.
        // The child is now adopted by `init` (PID 1) or another system process.
        printf("\nWe are in child process after sleep %d and our parrent is %d\n", getpid(), getppid());
    }
    
    // The original parent prints this message before exiting.
    if(x == getpid())
        printf("End the parrent process...\n");
    return(0);
}