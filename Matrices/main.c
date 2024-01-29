#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <functions.h>
#include <matrices.h>

#define PI 3.14159265358979	

#define zeros		0
#define ones 		1
#define identity	2
#define undefined	3



int main(){

  Matrix mat1;
  double euler[3];
  double euler1[3];
  double quat[4];
  double quat1[4];
  
  mat1 = create_mat(3,3);
  
  euler[0] = 0.0;
  euler[1] = 0.0;
  euler[2] = 250*PI/180;
  
  euler2DCM(euler,mat1);
  
  DCM2quat(mat1, quat);
  
  print_Matrix(&mat1);
  
  printf("\n-------------\n");
  
  for(int i=0; i<4; i++)
  	printf("%f\n\r",quat[i]);
  	
  printf("\n-------------\n");
  
  euler2quat(euler, quat1);
  	
  for(int i=0; i<4; i++)
  	printf("%f\n\r",quat1[i]);

  printf("\n-------------\n");
   	
   quat2euler(quat,euler1);
  	
  for(int i=0; i<3; i++)
  	printf("%f\n\r",180*euler1[i]/PI);
  
  exit(EXIT_SUCCESS);
}






