#include <stdio.h>

int main(){
  
 #ifdef ENABLE_MACRO
 	printf("Macro defined\n");
 #else
 	printf("Macro undefined\n");
 #endif

  printf("Finish TEST \n");
  
  return 0;
}

