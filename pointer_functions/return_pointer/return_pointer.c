#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct rectangle{
   float brd, len;
   double area;
};

struct rectangle *area(float x, float y);

int *sum(int a, int b){static int c=0; c=a+b; return &c;}
float *arrfunct(int x);

int main(){
 
   int *result;
   
   result=sum(10,20);
   printf("The result of sum is: %d\n\r", *result);
   
   int x1=10;
   float *array=arrfunct(x1);
   printf("Square of %d is %f\n\r", x1, array[0]);
   printf("Cube of %d is %f\n\r", x1, array[1]);
   printf("Square of root %d is %f\n\r", x1, array[2]);
   
   printf("=======================================\n\r");
   
   struct rectangle *r;
   float x, y;
   x=10; y=2;
   r = area(x,y);
   printf("Len: %f, Width: %f Area: %f \n\r",r->len, r->brd, r->area);  
  
  return 0;
}

struct rectangle *area(float x, float y)
{
   double area=(double)(x*y);
   static struct rectangle r;
   
   r.len=x; r.brd=y; r.area=area;
   return &r; 
}

float *arrfunct(int x)
{
   static float arr[3];
   arr[0]=pow(x,2);
   arr[1]=pow(x,3);
   arr[2]=pow(x,0.5);
   return arr;
}
