#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define NUM_THREAD 16
#define SEMA_MAX 4

sem_t test_sema;

void* routine_sema(void *args){

    int user_id = *(int*)args;
    // We will see NUM_THREAD amount of the following print
    printf("[QUEUE] USER %d waiting for log in\n", user_id);

    // sem_wait will decrement SEMA_MAX in each thread until zero.
    // If SEMA_MAX reaches 0, the next thread will be blocked until another thread calls sem_post().
    sem_wait(&test_sema);

    printf("[LOGIN] USER %d has logged in\n", user_id);
    sleep(rand() % 5 + 1);

    // sem_post will increment SEMA_MAX in each thread after it finishes,
    // allowing a blocked thread (if any) to proceed.
    sem_post(&test_sema);
    
    printf("\n[LOG OUT] USER %d has logged out\n", user_id);


    free(args);
    return  NULL;
}

int main(void){

    int i = 0;
    pthread_t t[NUM_THREAD];
    srand(time(NULL));

    // third  parametrs means how many threads at the same time will running 
    sem_init(&test_sema, 0, SEMA_MAX);

    for(i = 0; i < NUM_THREAD; i++){
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&t[i], NULL, &routine_sema, a)){
            printf("Something wrong during creating thread with index %d\n", i);
        }
    }
    for(i = 0; i < NUM_THREAD; i++){
        if(pthread_join(t[i], NULL)){
            printf("Something wrong during joining thread with index %d\n", i);
        }
    }

    sem_destroy(&test_sema);

    return(0);
}