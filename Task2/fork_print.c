#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void){

    int n = 1;

    int fid = fork();
    if(fid == 0){
        // Child process will print first 5 numbers
        for(int i = n; i < 6; i++)
            printf(" %d ", i);
    } else {
        // We need this wait because without it first we will have output from
        // the main process and only after that child process output
        wait(NULL);
        // Parrent process will print last 5 numbers
        for(int i = 6; i < 11; i++)
            printf(" %d ", i);
        printf("\nEnd in main process\n");
    }
    return(0);
}