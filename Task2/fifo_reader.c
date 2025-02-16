#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define NUM 6

int main(void){

    int arr[NUM];

    int fd = open("f_file", O_RDONLY, 0666);

    if(fd == -1){
        perror("open error");
        return 1;
    } else{
        for(int i = 0; i < NUM; i++){
            if (read(fd, &arr[i], sizeof(int)) == -1){
                perror("read error");
                return 2;
            }
            printf("Read the value %d\n", arr[i]);
        }
    }
    close(fd);
    
    return(0);
}