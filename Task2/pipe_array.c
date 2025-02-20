#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
    int fd[2];
    int f_id;

    if(pipe(fd) == -1){
        perror("pipe error");
        return 1;
    }
    f_id = fork();
    if(f_id == -1){
        perror("fork error");
        return 2;
    }
    if(f_id == 0){ // Child Process
        puts("We are in child  process");
        srand(time(NULL));
        close(fd[0]);
        int arr[20];
        int n = (rand() % 19) + 1;

        puts("Generated Array");
        for(int i = 0; i < n; i++){
            arr[i] = rand() % 100;
            printf(" %d", arr[i]);
            fflush(stdout);
        }
        write(1, "\n", 1);
        if(write(fd[1], &n, sizeof(n)) == -1){
            perror("write error array size child");
            exit(3);
        }
        if(write(fd[1], arr, sizeof(int) * n) == -1){
            perror("write error array child");
            exit(3);
        }
        close(fd[1]);
    } else{ // Parent process
        puts("We are in parent process");
        close(fd[1]);
        int arr2[20];
        int n2;

        if(read(fd[0], &n2, sizeof(n2)) == -1){
            perror("read error array size parent");
            return 5;
        }
        if(read(fd[0], &arr2, sizeof(int) * n2) == -1){
            perror("read error array parent");
            return 6;
        }
        close(fd[0]);
        puts("We recieved in parent process");
        for(int i = 0; i < n2; i++){
            printf(" %d", arr2[i]);
            fflush(stdout);
        }
        write(1, "\n", 1);
        wait(NULL);
    }

    return (0);
}