#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<stdlib.h>

#define NUM_THREAD 8
#define MAX_ROUNDS 8

pthread_barrier_t barrierDice;
pthread_barrier_t barrierCalc;

int diceValues[NUM_THREAD];
int status[NUM_THREAD] = {0};


void* roll_dice(void* args){

    int index = *(int*)args;

    for (int i = 0; i < MAX_ROUNDS; i++){
        diceValues[index] = (rand() % 6) + 1;
        
        // We need to wait here, until all threads randomize and store the value
        pthread_barrier_wait(&barrierDice);
        // This one barrier guarantes that printing status is always executing after all status was setted in 
        // the main thread
        pthread_barrier_wait(&barrierCalc);
        if(status[index] == 1){
            printf("Thread %lu, Index (%d) I won with %d\n", pthread_self(), index, diceValues[index]);
        } else {
            printf("Thread %lu, Index (%d) I lose with %d\n", pthread_self(), index, diceValues[index]);
        }
    }
    free(args);
    return NULL;
}

int main(void){
    srand(time(NULL));
    pthread_t th[NUM_THREAD];

    pthread_barrier_init(&barrierDice, NULL, NUM_THREAD + 1);
    pthread_barrier_init(&barrierCalc, NULL, NUM_THREAD + 1);


    for(int i = 0; i < NUM_THREAD; i++){
        int* r = malloc(sizeof(int));
        *r = i;
        if(pthread_create(&th[i], NULL, &roll_dice, r))
            printf("Error in thread creation %lu",pthread_self());
    }

    for (int i = 0; i < MAX_ROUNDS; i++) {
        printf("\n=====Round %d is started=====\n", i+1);
        //We need to wait here before  calculation
        // When all threads randomize and store the value we can run checker and changed the status array as for now we know
        // that all thread already done and stored the value
        pthread_barrier_wait(&barrierDice);
        int max = 0;
        for(int i = 0; i < NUM_THREAD; i++){
            if (diceValues[i] > max)
                max = diceValues[i];
        }
        for(int i = 0; i < NUM_THREAD; i++){
            if (diceValues[i] == max){
                status[i] = 1;
            } else
                status[i] = 0;
        }
        // And now before joining and destroying thread we need to wait that all info was calculated
        pthread_barrier_wait(&barrierCalc);
        sleep(1);
    }
    for(int i = 0; i < NUM_THREAD; i++){
        if(pthread_join(th[i], NULL))
            printf("Error in thread joining %lu", pthread_self());
    }
    
    puts("\nGame is over");
    pthread_barrier_destroy(&barrierDice);
    pthread_barrier_destroy(&barrierCalc);

    return(0);
}