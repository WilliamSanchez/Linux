#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sw = 0;

typedef enum {	Estado_0,
	 	Estado_1,
	 	Estado_2,
	 	Estado_3,
	 	Estado_4,
	 	No_de_estados 		 
}ESTADOS;

ESTADOS Estado_Actual = Estado_0;

typedef struct {
	ESTADOS Estado;
	void (*func)(int);

}FSM; 

void Codigo_EDO_0(int);
void Codigo_EDO_1(int);
void Codigo_EDO_2(int);
void Codigo_EDO_3(int);
void Codigo_EDO_4(int);

FSM State_Machine[]={
	{Estado_0,Codigo_EDO_0},
	{Estado_1,Codigo_EDO_1},
	{Estado_2,Codigo_EDO_2},
	{Estado_3,Codigo_EDO_3},		
	{Estado_4,Codigo_EDO_4},
};

int main(int argc, char **argv){

   while(1){
         if (getchar() == '0')
 	    sw = 0;
         else
	    sw = 1;
         getchar();
         // Estado_Actual is the position inside of the array FSM, 
	 // Estado_Actual represent the number according to enum.
         (*State_Machine[Estado_Actual].func)(sw);
   }
   return 0;
}



void Codigo_EDO_0(int sw){
   
   printf("Estado [0]");

   if(sw == 0){
     Estado_Actual = Estado_1;
     printf("Proximo stado [1]");
   }else{
     Estado_Actual = Estado_4;
     printf("Proximo stado [4]");
   }
}

void Codigo_EDO_1(int sw){
   
   printf("Estado [1]");

   if(sw == 0){
     Estado_Actual = Estado_2;
     printf("Proximo stado [2]");
   }else{
     Estado_Actual = Estado_4;
     printf("Proximo stado [4]");
   }
}

void Codigo_EDO_2(int sw){
   
   printf("Estado [2]");

   if(sw == 0){
     Estado_Actual = Estado_3;
     printf("Proximo stado [3]");
   }else{
     Estado_Actual = Estado_1;
     printf("Proximo stado [1]");
   }
}

void Codigo_EDO_3(int sw){
   
   printf("Estado [3]");

   if(sw == 0){
     Estado_Actual = Estado_4;
     printf("Proximo stado [4]");
   }else{
     Estado_Actual = Estado_2;
     printf("Proximo stado [2]");
  }
}

void Codigo_EDO_4(int sw){
   
   printf("Estado [4]");

   if(sw == 0){
     Estado_Actual = Estado_1;
     printf("Proximo stado [1]");
   }else{
     Estado_Actual = Estado_3;
     printf("Proximo stado [3]");
  }
}

