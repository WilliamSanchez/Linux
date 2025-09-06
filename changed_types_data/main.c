#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

float const dados[2] = {981.456, -567.9545};
char dado_main[4] = {0xd5, 0x78,0xe9,0x3e};
float fdado;

int main()
{
   for(uint8_t i=0; i<sizeof(dado_main); i++)
   	printf("%x|",(uint8_t)dado_main[i]);
   	
   printf("\n\r");	
   memcpy(&fdado,dado_main,sizeof(dado_main));
   printf("%f|",fdado);
   
   ///////////////////////////////////////////////
   
   char *char_dados = (char*)malloc(4*sizeof(char));
   printf("\n\rDados: %f, %f\n\r", dados[0],dados[1]);

   memcpy(char_dados,(uint8_t*)(dados+1),4*sizeof(char));
   
   for(int i=0; i<sizeof(dado_main); i++)
   	printf("%x|",char_dados[i]);
   	
   printf("\n\r");	
   memcpy(&fdado,char_dados,4*sizeof(char));
   printf("%f\n\r",fdado);
  
    ///////////////////////////////////////////////

   memcpy(char_dados,dados,4*sizeof(char));
   
   for(int i=0; i<sizeof(dado_main); i++)
   	printf("%x|",char_dados[i]);
   	
   printf("\n\r");	
   memcpy(&fdado,char_dados,4*sizeof(char));
   printf("%f",fdado);
   	
   printf("\n\r");
   free(char_dados);
 
}

  
  
  /* 	
   int dado1 = 0xFFFFFFFF;
   int dado = 0;
   dado = 0xFFFFFFFF&(uint8_t)dado_main[3];
   dado1 =dado;
   printf("\n\rdado1 %x\n\r",dado1);
   dado = 0xFFFFFFFF&(uint8_t)dado_main[2];
   dado <<=8;
   dado1 |= dado;
   printf("dado1 %x\n\r",dado1);
   dado = 0xFFFFFFFF&(uint8_t)dado_main[1];
   dado <<=16;
   dado1 |= dado;
   printf("dado1 %x\n\r",dado1);
   dado = 0xFFFFFFFF&(uint8_t)dado_main[0];
   dado <<=24;
   dado1 |= dado;
   printf("dado1 %x\n\r",dado1);
   	
   printf("\n\r");
   return 0;
   */

/*

   //char *char_dados = (char*)malloc(100*sizeof(char));
   char *char_dados[4];
   printf("Dados: %f, %f\n\r", dados[0],dados[1]);

   memcpy(char_dados,dado_main,sizeof(dado_main));
   
   printf("dado %f\n\r",dados[0]);
   
   for(int i=0; i<sizeof(dado_main); i++)
   	printf("%x|",char_dados[i]);
   	
   int dado1 = 0xFFFFFFFF;
   int dado = 0;
   //dado1 = (int)((dado1&(char_dados[3]<<24))&(dado1&(char_dados[2]<<16))&(dado1&(char_dados[1]<<8))&char_dados[0]);
   dado = 0x00000000|char_dados[0];
   dado1 =dado;
   printf("\n\rdado1 %x\n\r",dado1);
   dado = 0x00000000|(char_dados[1]);
   dado <<=8;
   dado1 = dado;
   printf("dado1 %x\n\r",dado1);
   
   
   printf("\n\rdado %f\n\r",dados[1]);
   	
   for(int i=sizeof(dados)/2; i<sizeof(dados); i++)
   	printf("%02x|",char_dados[i]);
   	
   printf("\n\r");

   //free(char_dados);

*/
