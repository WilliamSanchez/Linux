#ifndef _MISC_H_
#define _MISC_H_

#include <stdio.h>

typedef struct{
    int row;
    int col;
    double **data;
}Matrix;

Matrix create_mat(int row, int col);
double norm(Matrix mat);

Matrix fill_matrix(Matrix mat);

int matrix_free(Matrix mat);
void print_Matrix(Matrix *_matrix);


#endif
