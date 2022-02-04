#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

  char *args[]={"./program",NULL};

   printf("Running ps with execlp\n");
   //execlp("ps","ps","ax",(char*)NULL);
   execlp("./program","./program",NULL,(char*)NULL);
   //execvp(args[0],args);
   //execv(args[0],args);
   //system("~/Documents/code_C/Process/execute_programs/program");
   printf("Done.\n");
   exit(0);

}
