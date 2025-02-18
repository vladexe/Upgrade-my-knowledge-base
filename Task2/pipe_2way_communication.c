#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

int main(void){
    
    srand(time(NULL));
    // one pipe is for sending from child to parent
    // another pipe is for sending from parent to child
    int fd_1[2], fd_2[2];
    int fork_id;
    
    if(pipe(fd_1) == -1){
        perror("1 pipe error");
        return 1;
    }
    if(pipe(fd_2) == -1){
        perror("2 pipe error");
        return 2;
    }
    fork_id = fork();

    if(fork_id == -1){
        perror("fork error");
        return 3;
    }
    if(fork_id == 0){ // Child process
        int ch_random;
        close(fd_1[1]);
        close(fd_2[0]);
        if(read(fd_1[0], &ch_random, sizeof(ch_random)) == -1){
            perror("read error");
            return 4;
        }
        close(fd_1[0]);
        printf("We are in the child process and parent sent to us next number %d\n", ch_random);
        ch_random *= 3;
        if(write(fd_2[1], &ch_random, sizeof(ch_random)) == -1){
            perror("child write error");
            return 6;
        }
        close(fd_2[1]);
    }else { // Parent process
        int random = rand() % 10;
        close(fd_1[0]);
        close(fd_2[1]);
        if(write(fd_1[1], &random, sizeof(random)) == -1){
            perror("write error");
            return 5;
        }
        close(fd_1[1]);
        printf("We are in the parent process and we sent to child next number %d\n", random);
        
        // We need to wait until child process recieve our number, calculate and sent it
        // to another pipe, and only after that we can procede
        wait(NULL);
        if(read(fd_2[0], &random, sizeof(random)) == -1){
            perror("parent read error");
            return 7;
        }
        close(fd_2[0]);
        printf("We are in the parent process and child return to us %d\n", random);
    }
    return (0);
}