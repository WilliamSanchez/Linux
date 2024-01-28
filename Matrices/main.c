#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <matrices.h>

#include <math.h>

#define PI 3.14159265358979	

Matrix euler2DCM(Matrix euler, Matrix DCM);

int main(){

  Matrix matr;
  Matrix vector;
  Matrix dcm;
  
  matr = create_mat(3,3);
  dcm = create_mat(3,3);
  vector = create_mat(3,1);
    
  fill_matrix(matr);  
  print_Matrix(&matr);
  
  printf("\n-------------\n");
  
  vector.data[0][0]= 0.0;
  vector.data[1][0]= 0.0;
  vector.data[2][0]= 250*PI/180;
    
  print_Matrix(&vector);
 
   printf("\n------------- %f\n",cos(PI/4));
  
  euler2DCM(vector, dcm);
  print_Matrix(&dcm);
  
  if(matrix_free(matr) == 0)
      printf("Not free matrix\n\r");
  
    if(matrix_free(vector) == 0)
      printf("Not free vector\n\r");
  
  exit(EXIT_SUCCESS);
}



Matrix euler2DCM(Matrix euler, Matrix DCM)
{

    double cPHI,sPHI,cTHE,sTHE,cPSI,sPSI;
    
    cPHI = cos(euler.data[0][0]); sPHI = sin(euler.data[0][0]);
    cTHE = cos(euler.data[1][0]); sTHE = sin(euler.data[1][0]);
    cPSI = cos(euler.data[2][0]); sPSI = sin(euler.data[2][0]); 

    DCM.data[0][0]= cTHE*cPSI; 			DCM.data[0][1]= cTHE*sPSI; 			DCM.data[2][0]= -sTHE;
    DCM.data[1][0]= sPHI*sTHE*cPSI-cPHI*sPSI;	DCM.data[1][1]= sPHI*sTHE*sPSI+cPHI*cPSI;	DCM.data[2][1]= sPHI*cTHE;
    DCM.data[2][0]= cPHI*sTHE*cPSI+sPHI*sPSI;	DCM.data[2][1]= cPHI*sTHE*sPSI-sPHI*cPSI;	DCM.data[2][2]= cPHI*cTHE;

    return DCM;
}

