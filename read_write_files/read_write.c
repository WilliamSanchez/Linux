#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static FILE *fp, *wp;
static char c;
static char conteudo[1024];
static size_t numchar = 0;

extern void int_handler();

void main(int argc, char **argv)
{

   if(argc < 2){
   	printf("Input a file to send\n");
	exit(-1);
   }
   fp = fopen(argv[1],"ra+");
   wp = fopen("test_out.txt","w");
  
   
   while((c=fgetc(fp)) != EOF)
   {	
   	numchar++;
   	fputc(c,wp);
       	putchar(c);
   }
   
  // fread(&conteudo,sizeof(char),1024,fp);
  // printf("Arquivo: %s\n",conteudo);
   
  // fwrite(&conteudo,sizeof(char),strlen(conteudo),wp);
   
   fclose(fp);
   fclose(wp);
   signal(SIGINT,int_handler);

}


extern void int_handler()
{

  char ch;
  printf("Enter y to close sockets or n to keep open:");
  
  scanf("%c",&ch);
  if(ch == 'y')
  {
  	printf("\nsockets are being closed\n");
  
  }
  
  printf("Server: shutting down ...\n");
  exit(0);

}
