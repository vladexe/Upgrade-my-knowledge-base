#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>

#define THREAD_NUM 8
#define SIZE_BUF 10
#define MAX_CYCLES 20


int buffer[SIZE_BUF];
int count = 0;

pthread_mutex_t count_mutex;

sem_t empty_sem;
sem_t full_sem;


void* consumer(void *args){

    for(int i = 0; i < MAX_CYCLES; i++){
        int y = -1;
        sem_wait(&full_sem);
        pthread_mutex_lock(&count_mutex);
        
        y = buffer[count - 1];
        count--;

        pthread_mutex_unlock(&count_mutex);
        sem_post(&empty_sem);
        printf("Consumer [%lu] consumed: %d\n", pthread_self(), y);
        sleep(1);
    }
    return NULL;
}

void* producer(void *args){

    for(int i = 0; i < MAX_CYCLES; i++){
        int x = rand() % 100;
        sleep(1);
        sem_wait(&empty_sem);
        pthread_mutex_lock(&count_mutex);
       
        printf("Producer [%lu] produced: %d\n", pthread_self(), x);
        buffer[count] = x;
        count++;
        
        pthread_mutex_unlock(&count_mutex);
        sem_post(&full_sem);

    }
    return NULL;
}

int main(void){

    int i = 0;
    pthread_t t[THREAD_NUM];
    srand(time(NULL));


    pthread_mutex_init(&count_mutex, NULL);
    sem_init(&empty_sem, 0, SIZE_BUF);
    sem_init(&full_sem, 0, 0);

    for(i = 0;  i < THREAD_NUM; i++){
        if (i % 2 == 0){
            if(pthread_create(&t[i], NULL, &producer, NULL))
                printf("Error creating producer thread %d\n", i);
        } else
            if(pthread_create(&t[i], NULL, &consumer, NULL))
                printf("Error creating consumer thread %d\n", i);        
    }
    for(i = 0; i < THREAD_NUM; i++){
        if(pthread_join(t[i], NULL))
            printf("Something wrong during %d thread joining\n", i);
    }

    pthread_mutex_destroy(&count_mutex);
    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);

    return(0);
}