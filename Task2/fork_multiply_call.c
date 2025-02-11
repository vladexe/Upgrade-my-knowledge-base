#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

int main(void){
    
    int id_1 = fork();
    int id_2 = fork();

    // now we have 4 processes because of n^2 where n is fork calling amount

    if(id_1 == 0){
        if(id_2 == 0)
            puts("We are in Z(4) process");
        else
            puts("We are in Y(3) process");
    } else {
        if(id_2 == 0)
            puts("We are in X(2) process");
        else
            puts("We are in the parrent process");
    }
    while(wait(NULL) > 0);
}