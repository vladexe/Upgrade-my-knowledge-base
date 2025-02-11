#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void){

    pid_t x = getpid();
    int c = fork();

    if(c == 0){
        pid_t y = getpid();
        printf("\nHello this is a child process and my pid %d and my parrent is %d!!!\n", y, getppid());
    } else {
        sleep(1);
        printf("\nHello this is a parent process and my pid %d!!!\n", x);
    }

    return(0);
}