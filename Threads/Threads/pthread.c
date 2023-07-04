#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <omp.h>

int run_now = 2;

void *function1(void *arg){
    for(int i=0; i< 100; i++){
 	printf("X");
    }printf("\n\r");
    sleep(1);
    return NULL;
}

void *function2(void *arg){
    for(int i=0; i< 100; i++){
 	printf("Y");
    }printf("\n\r");
    sleep(1);
    return NULL;
}

int main(){
  
   
    pthread_t a_thread1;
    pthread_t a_thread2;
    printf("Estoy en el MAIN\n\r");
    pthread_create(&a_thread1,NULL,function1,NULL);
    pthread_create(&a_thread2,NULL,function2,NULL);
    for(int i=0; i< 100; i++){
 	printf("Z");
    }printf("\n\r");
    sleep(1);
    pthread_join(a_thread1,NULL);
    pthread_join(a_thread2,NULL); 
 

    return 0;
}
