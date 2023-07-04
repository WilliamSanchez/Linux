#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *function1(void *arg);
void *function2(void *arg);

pthread_mutex_t work_mutex;

int main(){

    int res;
    pthread_t a_thread, b_thread;

    res = pthread_mutex_init(&work_mutex,NULL);
    if(res != 0){
       perror("Mutex creation fail");
       exit(EXIT_FAILURE);
    }
   
    res = pthread_create(&a_thread,NULL,function1,NULL);
    if(res != 0){
       perror("Thread Creation fail");
       exit(EXIT_FAILURE);
    }
    res  = pthread_create(&b_thread,NULL,function2,NULL);
    if(res != 0){
       perror("Thread Creation fail");
       exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&work_mutex);
    for(int i=0; i< 5000; i++){
 	printf("Z");
    }printf("\n\r");
    pthread_mutex_unlock(&work_mutex);
    sleep(1);

    pthread_join(a_thread,NULL);
    pthread_join(b_thread,NULL);
   
    pthread_mutex_destroy(&work_mutex);

    return 0;
}

void *function1(void *arg){  
    pthread_mutex_lock(&work_mutex);
    for(int i=0; i< 5000; i++){
 	printf("X");
    }printf("\n\r");
    pthread_mutex_unlock(&work_mutex);
    sleep(1);
    return NULL;
}

void *function2(void *arg){  
    pthread_mutex_lock(&work_mutex);
    for(int i=0; i< 5000; i++){
 	printf("Y");
    }printf("\n\r");
    pthread_mutex_unlock(&work_mutex);
    sleep(1);
    return NULL;
}

