#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define NUMBER_OF_THREADS 7

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

int fuel_amount = 0;

void* filling_fuel(){

    for(int i =  0; i < 10; i++){
        // we lock the mutex when we changed the global variable
        pthread_mutex_lock(&mutexFuel);

        fuel_amount += 15;
        printf("\nFilling the OKKO with A95 + 15");
        printf("\nCurrent balance A95: %d", fuel_amount);
        //and unlock after successfully changing

        pthread_mutex_unlock(&mutexFuel);

        // in previous version we sent the signal only to one thread
        // as we have only 1 car, but if we want to fill more than 1 car
        // we need to broadcast this signal
        pthread_cond_broadcast(&condFuel);
        sleep(1);
    }
}

void* car(){

    //we lock the mutex before fueling the car
    pthread_mutex_lock(&mutexFuel);

    while (fuel_amount < 40){
        printf("\nCar OUTPUT: No FUEL!!!");
        pthread_cond_wait(&condFuel, &mutexFuel);
        //and what we done here
        //     we unlock our mutex
        //     wait for signal
        //     lock again
    }
    fuel_amount -= 40;
    printf("\n\nGetting the A95 - 40");
    printf("\nCurrent balance A95: %d", fuel_amount);
    pthread_mutex_unlock(&mutexFuel);
}

int main(void){

    pthread_t t[NUMBER_OF_THREADS];

    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; i++){
        if (i == 0 || i == 1){
            if (pthread_create(&t[i],NULL, &filling_fuel, NULL))
                perror("Something wrong with fuel thread creation");
        } 
        else if (pthread_create(&t[i], NULL, &car, NULL)){
            perror("Something wrong  with car thread creation");
        }
    }
    for (int i = 0; i < NUMBER_OF_THREADS; i++){
        if (pthread_join(t[i], NULL)){
            perror("Something wrong with thread creation");
        }   
    }

    printf("\n");
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return (0);
}