#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void){
    
    int start, end;
    int arr[] = {6, 1, 5, 2, 3, 9, 10};
    // Sizeof arr gives us amount of bytes in this array, but not amount of numbers
    int arrSize = sizeof(arr) / sizeof(int);
    int fd[2];

    if(pipe(fd) == -1){
        perror("Pipe error");
        return 1;
    }

    int f_id = fork();

    if(f_id == -1){
        perror("Fork error");
        return 2;
    }

    if(f_id == 0){
        start = 0;
        end = arrSize / 2; 
    } else{
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;

    for(int i = start; i < end; i++){
        sum += arr[i];
    }

    printf("Result partial sum  %d\n", sum);  

    if(f_id == 0){ // Child process
        close(fd[0]);
        if(write(fd[1], &sum, sizeof(int)) == -1){
            perror("write error");
            // exit with 3 means some custom error happens
            exit(3);
        }
        close(fd[1]);
    } else{ // Parent process
        int child_sum;

        // We need to wait until child process end the calculation
        // here is not representable, but in complex program we could 
        // calculate some wrong values in parrent, because of child
        // have not end the calculation yet 
        wait(NULL);
        close(fd[1]);
        if(read(fd[0], &child_sum, sizeof(int)) == -1){
            perror("read error");
            return 3;
        }
        close(fd[0]);
        sum += child_sum;
        printf("The final sum is %d", sum);
    }

    return(0);
}