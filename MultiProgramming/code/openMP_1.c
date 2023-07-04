#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS   3

int main(){

   int n=NTHREADS, tid =-1;
   
   #pragma omp parallel if(n>=1) num_threads(n) \
  		default(none) private(tid) shared(n)
   {
   
       //obtem o identificador de thread
       tid = omp_get_thread_num();
       
       printf("Thread %d: Hello!\n",tid);
       
       if(n != omp_get_num_threads())
   	      printf("Error: NTHREADS\n");
   }
   
   printf("Thread %d: Bye!\n",tid);
}
