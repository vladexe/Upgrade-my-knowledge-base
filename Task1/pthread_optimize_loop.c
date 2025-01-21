#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int mail = 0;
pthread_mutex_t mutex;

void* mail_server()
{
	printf("Thread %ld started\n", pthread_self());

	for(int i = 0; i < 10000; i++){
		pthread_mutex_lock(&mutex);
		mail++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(void){

	pthread_t ta[4];
	
	pthread_mutex_init(&mutex, NULL);

    // we just create simple SEPARATE loop for creating pthreads
    for(int i = 0; i < 4; i++){
        if (pthread_create(&ta[i], NULL, &mail_server, NULL)) {
		    perror("Issue during create thread");
		    return 1;
	    }
    }
    // and one more loop for joining
    for(int i = 0; i < 4; i++){
        if (pthread_join(ta[i], NULL)) {
                perror("Issue during create thread");
                return 1;
        }
    }
	  
	// we need to destroy mutex after joining all threads
	pthread_mutex_destroy(&mutex);
	printf("\nResult amount of mails: %d\n", mail);
	

	return (0);
}
