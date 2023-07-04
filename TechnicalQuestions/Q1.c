#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char *invertirString(char *string);
char **stringSplit(const char *text, char separator, int *length);
int hasFunction(char dato);

char prueba[]="hola como vamos";

char sudoku[9][9]={ {'5','3','4','6','7','8','9','1','2'},
             	    {'6','7','2','1','9','5','3','4','8'},
             	    {'1','9','8','3','4','2','5','6','7'},
             	    {'8','5','9','7','6','1','4','2','3'},
             	    {'4','2','6','8','5','3','7','9','1'},
             	    {'7','1','3','9','2','4','8','5','6'},
             	    {'9','6','1','5','3','7','2','8','4'},
             	    {'2','8','7','4','1','9','6','3','5'},
             	    {'3','4','5','2','8','6','1','7','9'}};
/*
char sudoku[9][9]={ {'5','3','4','6','7','8','9','1','2'},
             	    {'6','7','2','1','9','5','3','4','8'},
             	    {'1','9','8','3','4','2','5','6','7'},
             	    {'8','5','9','7','6','1','4','2','3'},
             	    {'8','5','9','7','6','1','4','2','3'},
             	    {'7','1','3','9','2','4','8','5','6'},
             	    {'9','6','1','5','3','7','2','8','4'},
             	    {'2','8','7','4','1','9','6','3','5'},
             	    {'3','4','5','2','8','6','1','7','9'}};
*/

int main(){

// Question 1
   
   printf("\t\t Question 1\n\r");
   char *invPrueba=(char*)malloc(strlen(prueba)*sizeof(char));
   memcpy(invPrueba,invertirString(prueba),strlen(prueba));
   printf("[%s] string invertido [%s]\n\r",prueba,invPrueba);   
   free(invPrueba);

// Question 2
   printf("\t\t Question 2\n\r");
   // Horizontal ....
   for(int i=0; i<9; i++){
      int saveHorizontal[9]={0,0,0,0,0,0,0,0,0};
       for(int j=0; j<9; j++){
            int index = (int)sudoku[i][j]%9;
 	    saveHorizontal[index]++; 
            printf("%c[%d]",sudoku[i][j],saveHorizontal[index]);
            if(saveHorizontal[index] >= 2){			//Horizontal  
		printf("\n\rNo es valido\n");
		goto out;         
            }

      }  
       printf("\n\r");
   }

       printf("-----------------------------------------------\n\r");
   // Vertical
   for(int i=0; i<9; i++){
      int saveVertical[9]={0,0,0,0,0,0,0,0,0};
       for(int j=0; j<9; j++){
            int index = (int)sudoku[j][i]%9;
 	    saveVertical[index]++; 
            printf("%c[%d]",sudoku[j][i],saveVertical[index]);
            if(saveVertical[index] >= 2){			//Horizontal  
		printf("\n\rNo es valido\n");
		goto out;         
            }
      }  
       printf("\n\r");
   }
  
   printf("\n\rEs valido\n\r");


// Question 3
   printf("\t\t Question 3\n\r");
   char stringQ3[]="/Hola/como/vamos,/bien/y/su/merced/kkk/Meu/Deus/do/santos/";
   int len = strlen(stringQ3);
   char **newString=(char**)malloc(200*sizeof(char*));;
   newString=stringSplit(stringQ3, '/', &len);
   int numLetter = (int)strlen((char*)newString); // Corregir el numero de array dentro del array
   printf("\n\r");
   for(int i=0;i<len;i++)
      printf("[%d]\t%s\n\r",i,(char*)&newString[i]);
   out:
   return 0;
}



char *invertirString(char *string){
  int len = 0;
  len = strlen(string);
  char *invString=(char*)malloc(len*(sizeof(char)));
  for(int i=0; i<len; i++)
       *(invString+i)=*(string+len-i-1);
  return invString;       
}

int hasFunction(char dato){
    int len = (int)dato;
    int suma = 0;
    for(int i=0; i<len; i++)
         suma++;
    return suma%9;
}

char **stringSplit(const char *text, char separator, int *length){
    
     int cont=0,s=0;
    printf("longitude Array [%d]\n\r",*length);
    // Option1
    char **auxString = (char**)malloc(20*sizeof(char*));
    // Option2
    // char *mat = (char*)malloc(rows*cols*sizeof(char));
    char *newArray=(char*)malloc(10*sizeof(char));
    memset(newArray,0x00,10);
    for(int i=0; i<=*length;i++){
          if(*(text+i) == '/' && cont){
               memcpy((char*)&auxString[s],newArray,strlen(newArray)); 
               printf("[%s]",(char*)&auxString[s]);
               memset(newArray,0x00,10);s++;cont=0;
          }else if(*(text+i) != '/'){
             *(newArray+cont)=*(text+i);cont++;
          }
    }
    *length = s;
    free(newArray);//free(auxString);
    return auxString;
}
