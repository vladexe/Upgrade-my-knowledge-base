#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(void){

    printf("\nI'm in parrent process with id %d\n", getpid());

    int x = fork();
    if(x == 0)
        exit(0);
    printf("Parrent is still alive\n");

    // The parent process sleeps for 20 seconds.
    // During this time, the child process exits but is not reaped (waited on).
    // This makes it a zombie process, visible using:
    //         ps aux | grep Z

    // Expected output example from `ps aux | grep Z`:
    // <user>  82984  0.0  0.0  0  0 pts/6    Z+   22:45   0:00 [fork_o] <defunct>
    //
    // Explanation:
    // - `82984`: Child process ID (now a zombie)
    // - `Z+`    : Indicates zombie state
    // - `<defunct>`: Means the process has exited but is waiting for the parent to reap it

    sleep(20);

    return(0);
}