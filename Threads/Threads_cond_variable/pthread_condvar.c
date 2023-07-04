#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define WORK_SIZE	10

int out, in, cont, buffer[WORK_SIZE];
pthread_cond_t lleno, vacio;
pthread_mutex_t semaf;

void Escribe(int DATO);
int Lee();
void *productor(void *arg);

int main(){
  
  int i;
  pthread_t hijo;
  in = out = cont = 0;
  pthread_mutex_init(&semaf,NULL);
  pthread_cond_init(&lleno,NULL);
  pthread_cond_init(&vacio,NULL);
  pthread_create(&hijo,NULL,productor,NULL);
  printf("PADRE\n");
  for(i=0;i<100;i++){
     printf("%d\n",Lee());
     sleep(1);
  }
  exit(0);  
}

void *productor(void *arg){
  int i;
  printf("HIJO\n");
  for(i=0;i<100;i++){
     Escribe(i);sleep(1);
  }
  pthread_exit(0);

}

void Escribe(int DATO){
  pthread_mutex_lock(&semaf);
  while(cont == WORK_SIZE)
     pthread_cond_wait(&vacio,&semaf);
  cont++;buffer[in]=DATO;
  in=(in+1)%WORK_SIZE;
  pthread_cond_broadcast(&lleno);
  pthread_mutex_unlock(&semaf);
}

int Lee(){
 
  int dato;
  pthread_mutex_lock(&semaf);
  while(cont == 0)
    pthread_cond_wait(&lleno,&semaf);
  cont--;dato=buffer[out];
  out = (out+1)%WORK_SIZE;
  pthread_cond_broadcast(&vacio);
  pthread_mutex_unlock(&semaf);
  return dato;

}
