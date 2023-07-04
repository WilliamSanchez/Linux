#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define WORK_SIZE 	1024

pthread_mutex_t work_mutex;
char work_area[WORK_SIZE];
int time_to_exit=0;

void *thread_function(void *arg);

int main(){

   int res;
   pthread_t a_thread;
   void *result_thread;
   res = pthread_mutex_init(&work_mutex,NULL);
   if(res != 0){
      perror("Mutex initialization failed");
      exit(EXIT_FAILURE);
   }
   res = pthread_create(&a_thread,NULL,thread_function,NULL);
   if(res != 0){
      perror("Thread initialization failed");
      exit(EXIT_FAILURE);
   }

   pthread_mutex_lock(&work_mutex);
   printf("Input some text. Enter 'end' to finish\n");
   while(!time_to_exit){
	fgets(work_area,WORK_SIZE,stdin);
        pthread_mutex_unlock(&work_mutex);
        while(1){
 	   pthread_mutex_lock(&work_mutex);
    	   if(work_area[0] != '\0'){
		pthread_mutex_unlock(&work_mutex);
                sleep(1);
           }else{
    		break;
           }
        }
   }


   pthread_mutex_unlock(&work_mutex);
   printf("\nWaiting for thread finish ....\n"); 
   res = pthread_join(a_thread,&result_thread);
   if(res != 0){
      perror("Thread join failed");
      exit(EXIT_FAILURE);
   }
   printf("Thread joined\n");
   pthread_mutex_destroy(&work_mutex);
   exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){  
  
  sleep(1);
  pthread_mutex_lock(&work_mutex);
  while(strncmp("end",work_area,3) != 0){
     printf("you input %d characters\n",(int)strlen(work_area)-1);
     work_area[0]='\0';
     pthread_mutex_unlock(&work_mutex);
     sleep(1);
     pthread_mutex_lock(&work_mutex);
     while(work_area[0] == '\0'){
	pthread_mutex_unlock(&work_mutex);
        sleep(1);
        pthread_mutex_lock(&work_mutex);
     }
  }
  time_to_exit = 1;
  work_area[0] = '\0';
  pthread_mutex_unlock(&work_mutex);
  pthread_exit(0);  
}











