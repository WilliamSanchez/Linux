#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <functions.h>
#include <matrices.h>

#define PI 			3.14159265358979
#define e			0.00335289186		// 1/298.25 
#define Ro			6.378138E6		// [m]
#define omega			7.292115E-5		// rad/s
#define go			9.780327		// m/s²		

#define zeros		0
#define ones 		1
#define identity	2
#define undefined	3

#define RE(x)(Ro*(1+e*sin(x)*sin(x))) 
#define RN(x)(Ro*(1-e*(2-3*sin(x)*sin(x))))
#define Re(x)(Ro*(1-e*sin(x)*sin(x))) 

int main(){

  Matrix mat1, mat2;
  double euler[3];
  double euler1[3];
  double quat[4];
  double quat1[4];
  double teste[3], testeQ[4];
  
  mat1 = create_mat(3,3);
  mat2 = create_mat(4,4);
  
  euler[0] = 0.0;
  euler[1] = 0.0;
  euler[2] = 250*PI/180;
  /*
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
  	
   printf("\n-------------\n");	
  	
  DCM_Angular(euler, mat2);
  
    print_Matrix(&mat2);

  printf("\n-------------\n");
  
   double delta = 0.5;
   
   
   teste[0]= 4; teste[1] =2; teste[2]=3;
   testeQ[0]=1; testeQ[1]=2; testeQ[2]=1; testeQ[3]=1;
   
   rungeKutta(mat2, teste, testeQ, delta, quat1);
    */
   printf("\n-------------\n");
   
   printf("\n-----Ro [%f] ---\n",Ro);
   printf("\n-----omega [%f] ---\n",omega);
   
   printf("\n-----RE [%f] ---\n",RE(45*PI/180));
   printf("\n-----RN [%f] ---\n",RN(45*PI/180));
   printf("\n-----Re [%f] ---\n",Re(45*PI/180));
   
   printf("\n-----Quaternion ---\n");
   /*
   quat[0]=1; quat[1]=4; quat[2]=5; quat[3]=8;
   quat1[0]=3; quat1[1]=1; quat1[2]=5; quat1[3]=7;
  
  sumQuat(quat, quat1, testeQ);
  
    for(int i=0; i<4; i++)
  	printf("%f\n\r",testeQ[i]);
  
  printf("\n-------------\n");
  
    prodQuat(quat1, quat, testeQ);
  
    for(int i=0; i<4; i++)
  	printf("%f\n\r",testeQ[i]);
  
  printf("\n-------------\n");
  
  double invQ[4];
  
    invQuat(quat1,invQ);
  
    for(int i=0; i<4; i++)
  	printf("%f\n\r",invQ[i]);
  
   printf("\n-------------\n");
  
    prodQuat(quat, invQ, testeQ);
  
    for(int i=0; i<4; i++)
  	printf("%f\n\r",testeQ[i]);
  
   printf("\n-------------\n");
  
    divQuat(quat,quat1,testeQ);
  
    for(int i=0; i<4; i++)
  	printf("%f\n\r",testeQ[i]);
  */
  printf("\n-------------\n");
  
  exit(EXIT_SUCCESS);
}






