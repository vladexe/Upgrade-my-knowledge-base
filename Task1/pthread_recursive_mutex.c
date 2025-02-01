#include<stdio.h>
#include<pthread.h>

pthread_mutexattr_t attr_mutex;
pthread_mutex_t rec_mutex;


void* recursive_test(void *args){
    
    pthread_mutex_lock(&rec_mutex);
    //
    // if i  will add another one locking mechanism for this mutex it will jump into deadlock
    // but if mutex will be defined as recursive nothing bad happened if we will have the same 
    // lock call as an unlock call
    // 3 Mutex Lock + 3 Mutex Unlock for example
    // 
    pthread_mutex_lock(&rec_mutex);
    puts("Mutex succesfully locked");
    pthread_mutex_unlock(&rec_mutex);
    pthread_mutex_unlock(&rec_mutex);
    return NULL;
}

int main(void){
    
    pthread_t t;
    
    pthread_mutexattr_init(&attr_mutex);
    pthread_mutexattr_settype(&attr_mutex, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&rec_mutex, &attr_mutex);

    if(pthread_create(&t, NULL, &recursive_test, NULL))
        printf("There is an issue with thread creating\n");
    
    if(pthread_join(t, NULL))
        printf("Thereis an issue with thread joining\n");

    pthread_mutexattr_destroy(&attr_mutex);
    pthread_mutex_destroy(&rec_mutex);
    return (0);
}