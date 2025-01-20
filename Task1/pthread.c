#include<stdio.h>
#include<pthread.h>

void *thread_test_example(void *arg){

	int k = *(int *)arg;
	static int j = 42;
	printf("\nStart message from thread %d\n", k);
	printf("Starting point: %d",j++);
	sleep(2);
	printf("\nEnd message from thread %d\n",k);
}

int main(void){
	pthread_t thread_one, thread_two;
	int id_1 = 1, id_2 = 2;

	// Create a thread
    	if (pthread_create(&thread_one, NULL, thread_test_example, &id_1) != 0) {
        	perror("Failed to create thread");
        	return 1;
    	}
	// Create a thread
    	if (pthread_create(&thread_two, NULL, thread_test_example, &id_2) != 0) {
        	perror("Failed to create thread");
        	return 1;
    	}
    	// Wait for the thread to finish
    	if (pthread_join(thread_one, NULL) != 0) {
        	perror("Failed to join 1 thread");
        	return 1;
    	}
    	// Wait for the thread to finish
   	 if (pthread_join(thread_two, NULL) != 0) {
        	perror("Failed to join 2 thread");
        	return 1;
    	}
	return (0);
}
