#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>


int prime_array[10] = {2, 3, 5, 7, 9, 11, 13, 17, 19, 23 };

void* prime_number(void* arg){

    int v = *(int*)arg;
    printf("\nReturn nothing");
    printf("\nThe number from thread %d\n", prime_array[v]);
    free(arg);
}

int main(void){
    
    pthread_t thread_a[10];

    for(int i = 0; i < 10; i++){
        int *a = malloc(sizeof(int));
        *a = i;
        // One more example is to pass prime_array[i]
        if(pthread_create(&thread_a[i], NULL, &prime_number, a))
            printf("Something wrong during thread creating");
    }
    for(int i = 0; i < 10; i++){
        if(pthread_join(thread_a[i], NULL))
            printf("Something wrong during thread joining");
    }
    return (0);
}