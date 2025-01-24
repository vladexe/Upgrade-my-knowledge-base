#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define NUMBER_OF_THREADS 2

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

int fuel_amount = 0;

void* filling_fuel(){

    for(int i =  0; i < 5; i++){
        pthread_mutex_lock(&mutexFuel);
        fuel_amount += 15;
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
        printf("\nFilling the OKKO with A95 + 15");
        printf("\nCurrent balance A95: %d", fuel_amount);
        sleep(1);
    }
}

void* car(){

    pthread_mutex_lock(&mutexFuel);

    while (fuel_amount < 40){
        printf("\n\nCar OUTPUT: No FUEL!!!\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
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

    for (int i = 0; i < 2; i++){
        if (i == 0){
            if (pthread_create(&t[i],NULL, &car, NULL))
                perror("Something wrong with thread creation");
        } 
        else if (pthread_create(&t[i], NULL, &filling_fuel, NULL)){
            perror("Something wrong  with thread creation");
        }
    }
    for (int i = 0; i < 2; i++){
        if (pthread_join(t[i], NULL)){
            perror("Something wrong with thread creation");
        }   
    }

    printf("\n");
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return (0);
}