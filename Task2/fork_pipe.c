#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(void){

    //fd [0] - read end
    //fd [1] - write end
    int fd[2];

    // Create an unnamed pipe for inter-process communication (IPC)
    if(pipe(fd) == -1){
        perror("Pipe error");
        return 1;
    }
    int fork_id = fork();
    // Parent and child inherit fd[0] and fd[1], referring to the same pipe
    if(fork_id == -1){
        perror("Fork error");
        return 2;
    }

    if(fork_id == 0){  // Child Proce
        int x;
        //best practice is close fd[0] as we will write in this process and not read
        close(fd[0]);
        printf("Input a number\nWe are in process %d\n", getpid());
        scanf("%d", &x);

        if((write(fd[1], &x, sizeof(int)) == -1)){
            perror("Write error");
            exit(3);
        } 
        close(fd[1]);
        exit(0);
    } else { // Parent process
        // we need to wait in parent process until child process writing the value
        wait(NULL);
        int res;
        // we need to close uneeded fd for writing as we will only reading
        close(fd[1]);
        printf("Get from the pipe\n");

        // now as we now child process already end, 
        // we can read the buffer from pipe
        if(read(fd[0], &res, sizeof(int)) == -1){
            perror("Read error");
            return 4;
        }
        printf("Result if %d, we are in process %d\n", res, getpid());
        close(fd[0]);
    }
    return(0);
}