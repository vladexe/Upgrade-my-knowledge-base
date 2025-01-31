#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define NUMBER_OF_THREADS 10
#define MUTEX_AMOUNT 4
#define STOVE_FUEL 4

pthread_mutex_t stoveMutex[MUTEX_AMOUNT];
int stoveFuel[STOVE_FUEL] = {100, 100, 100, 100};


void *routine(void *arg){

    printf("\nThe message from thread %ld\n",pthread_self());

    for(int i = 0; i < 4; i++){
        if (pthread_mutex_trylock(&stoveMutex[i]) == 0){
            int fuelNeeded = rand() % 25;
            if (stoveFuel[i] - fuelNeeded < 0){
                puts("No more fuel... Just going home");
            } else {
                stoveFuel[i] -= fuelNeeded;
                printf("\nFuel left %d at stove %d", stoveFuel[i], i+1); 
            } 
            usleep(500000);
            pthread_mutex_unlock(&stoveMutex[i]);
            break;
        } else {
            if (i == 3) {
                puts("\nNot enough fuel please wait");
                usleep(300000);
                i = 0;
            }
        }
    }
    return NULL;
}

int main(void){

    srand(time(NULL));
    pthread_t t[NUMBER_OF_THREADS];


    for(int i = 0; i < 4; i++)
        pthread_mutex_init(&stoveMutex[i], NULL);
    for(int i = 0; i < NUMBER_OF_THREADS; i++){
        if(pthread_create(&t[i],NULL, &routine, NULL)){
            perror("Something going wrong during thread creation");
        }
    }
    for(int i = 0; i < NUMBER_OF_THREADS; i++){
        if(pthread_join(t[i],NULL)){
            perror("Something going wrong during thread joining");
        }
    }
    for(int i = 0; i < 4; i++)
        pthread_mutex_destroy(&stoveMutex[i]);
    return (0);
}