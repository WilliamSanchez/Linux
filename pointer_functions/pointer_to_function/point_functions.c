#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//return_type (*pointer_name)(parameter_types)

void hello(){printf("Hello world\n\r");}

int add(int a, int b){ return a+b;}
int multiply(int a, int b){ return a*b;}
int substraction(int a, int b){ return a-b;}
void swap(int *a, int *b){int c; c =*a; *a=*b; *b = c;};

void operate(int x, int y, int (*operation)(int,int))
{
   int result_operation = operation(x,y);
   printf("Result: %d\n\r", result_operation);
}

int main(int argc, char **argv){
 
  void (*ptr)()=&hello;
  (*ptr)();
  
  int (*add_pointer)(int, int)=add;
  int (*multiply_pointer)(int, int)=multiply;
  int (*substraction_pointer)(int, int)=substraction;
  
  int (*operations[])(int, int) = {add, multiply, substraction};
  
  int add_result = add_pointer(3,4);
  int multiply_result = multiply_pointer(3,4);
  int substraction_result = substraction_pointer(3,4);
  
  void (*ptr_swap)(int *, int *b) = swap;
  int x = 10, y = 20;
  
  printf("Result with add pointer function %d\n\r",add_result);
  printf("Result with multiciply pointer function %d\n\r",multiply_result);
  printf("Result with substraction pointer function %d\n\r",substraction_result);
  printf("=================================================\n\r");
  printf("Result inside on operations add function %d\n\r", operations[0](5,3));
  printf("Result inside on operations multiciply function %d\n\r",operations[1](5,3));
  printf("Result inside on operations substraction function %d\n\r",operations[2](5,3));
  printf("=================================================\n\r");
  operate(5,3,add);
  operate(5,3,multiply);  
  printf("=================================================\n\r");
  printf("values of x:%d, and y:%d before swap\n\r",x,y);
  (*ptr_swap)(&x,&y);
  printf("values of x:%d, and y:%d after swap\n\r",x,y);
  
  return 0;
}



