#include <matrices.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

Matrix create_mat(int row, int col)
{
    Matrix mat;
 
     double **data;
        
    mat.data = (double **)malloc(row*sizeof(double *));
    
    for(int j=0; j<row; j++)
    	*(mat.data+j) = (double *)malloc(col * sizeof(double));
    
   
    mat.row = row;
    mat.col = col;
  
    return mat;

}


double norm(Matrix mat)
{

   double mag = 0.0;
   for(int j=0; j< mat.row; j++)
   	mag += mat.data[i][0]*mat.data[i][0];
   	
  return sqrt(mag);
}

Matrix fill_matrix(Matrix mat)
{

    for(int j=0; j< mat.row; j++)
    {
      for(int i=0; i< mat.col; i++)
      {
      	 *(*(mat.data+i)+j) = i*j+1;
      
      }
    } 
    
    return mat;
}


int matrix_free(Matrix mat)
{
    if (mat.data == NULL)
       return 0;
       
    for(int j=0; j < mat.col; j++)
        free(*(mat.data+j));
    free(mat.data);
    
    return 1;

}


void print_Matrix(Matrix *_matrix)
{
    for(int i=0; i<_matrix->col; i++)
    { 
 	for(int j=0; j<_matrix->row; j++)
 	{
 		printf("%f ",_matrix->data[i][j]);
 	}
 	printf("\n\r");
    } 
 }
