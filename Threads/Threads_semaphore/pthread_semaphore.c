#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define WORK_SIZE	1024

sem_t bin_sem;
char work_area[WORK_SIZE];

void *thread_function(void *arg);


int main(int argc, char **argv){
 
    int res;
    pthread_t a_thread;
    void *thread_result;

    res = sem_init(&bin_sem,0,0);
    if(res!= 0){
       perror("Semaphore initialization failed");
       exit(EXIT_FAILURE);
    }
    res = pthread_create(&a_thread,NULL,thread_function,NULL);
    if(res!= 0){
       perror("Semaphore initialization failed");
       exit(EXIT_FAILURE);
    }
   
    printf("Input some text. Enter end to finish \n");
    while(strncmp("end",work_area,3)!=0){
	fgets(work_area,WORK_SIZE,stdin);
        sem_post(&bin_sem);	//increase the value of the semaphore 
    }  

    printf("\nwaiting for the thread to finish\n");
    res = pthread_join(a_thread,&thread_result);
    if(res!= 0){
       perror("thread join failed");
       exit(EXIT_FAILURE);
    }

    printf("pthread joined\n");
    sem_destroy(&bin_sem);
    return 0;
}


void *thread_function(void *arg){
  
  sem_wait(&bin_sem);		//decrease the value of the semaphore 
/*
  if sem_wait is called on a semaphore with a value of 0, the function will wait until a some other
   thread has incremented the value so that it is no longer 0
*/
  while(strncmp("end",work_area,3) != 0){
     printf("you input %d characters\n",(int)strlen(work_area)-1);
     sem_wait(&bin_sem);
  }
   pthread_exit(NULL);
}
