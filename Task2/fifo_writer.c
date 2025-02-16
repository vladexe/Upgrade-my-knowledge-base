#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define NUM 6

int main(void){
    
    srand(time(NULL));
    int array[NUM];

    printf("Hello from writing program\n");

    for(int i = 0; i < NUM; i++){
        array[i] = rand() %  100;
        printf("Generating numbers : %d\n", array[i]);
    }
    int fd = open("f_file", O_WRONLY, 0666);
    if (fd == -1){
        perror("open error");
        return 1;
    } else {
        write(fd, array, sizeof(int) * NUM);
    }
    close(fd);
    return(0);
}