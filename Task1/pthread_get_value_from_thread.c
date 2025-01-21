#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>    

pthread_mutex_t mutex;

void* dice_gambler()
{
    int dice = (rand() % 6) + 1;

    //we need to allcate memory for transfer the value to main thread
    int *res = malloc(sizeof(int));
    *res = dice;
    printf("\nThread %ld started and rolled a dice: %d\n", pthread_self(), dice);

	return (void *)res;
}

int main(void){

    srand(time(NULL));
	pthread_t ta[4];

    int* result;
	
    // we just create simple SEPARATE loop for creating pthreads
    for(int i = 0; i < 4; i++){
        if (pthread_create(&ta[i], NULL, &dice_gambler, NULL)) {
		    perror("Issue during create thread");
		    return 1;
	    }
    }
    // and one more loop for joining
    for(int i = 0; i < 4; i++){
        if (pthread_join(ta[i], (void **)&result)) {
                perror("Issue during join thread");
                return 1;
        }
        	printf("\nDice value for thread %d: %d\n",i, *result);
            // We need to free memory alocated in each thread
            free(result);

    }


	return (0);
}
