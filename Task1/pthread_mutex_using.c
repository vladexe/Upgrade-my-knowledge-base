#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int mail = 0;
pthread_mutex_t mutex;


//in that case without mutex I will recieve diferent results each time
//	./pthread_example 
//	Result amount of mails: 16150
//
//	./pthread_example 
//	Result amount of mails: 19080
//		


void* mail_server()
{
	printf("Thread %ld started\n", pthread_self());

	for(int i = 0; i < 10000; i++){
		//with lock in this cycle 
		// 	
		// 	./pthread_example 
		// 	Result amount of mails: 40000
		// We will recieve correct values 	
		pthread_mutex_lock(&mutex);
		mail++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(void){

	pthread_t t1,t2,t3,t4;
	
	// we need to init  mutex before  creating threads
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&t1, NULL, &mail_server, NULL)) {
		perror("Issue during create thread 1");
		return 1;
	}
	if (pthread_create(&t2, NULL, &mail_server, NULL)) {
                perror("Issue during create thread 2");
                return 1;
        }
	if (pthread_create(&t3, NULL, &mail_server, NULL)) {
                perror("Issue during create thread 3");
                return 1;
        }
	if (pthread_create(&t4, NULL, &mail_server, NULL)) {
                perror("Issue during create thread 4");
                return 1;
        }
	if (pthread_join(t1, NULL)) {
                perror("Issue during join thread 1");
                return 1;
        }
        if (pthread_join(t2, NULL)) {
                perror("Issue during join thread 2");
                return 1;
        }
        if (pthread_join(t3, NULL)) {
                perror("Issue during join thread 3");
                return 1;
        }
        if (pthread_join(t4, NULL)) {
                perror("Issue during join thread 4");
                return 1;
        }

	// we need to destroy mutex after joining all threads
	pthread_mutex_destroy(&mutex);
	printf("\nResult amount of mails: %d\n", mail);
	

	return (0);
}
