#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <matrices.h> 
#include <math.h>


Matrix euler2DCM(double *euler, Matrix DCM);
Matrix quat2DCM(double *quat, Matrix DCM);
double DCM2quat(Matrix DCM, double *quat);
double euler2quat(double *euler, double *quat);
double quat2euler(double *quat, double *euler);


#endif
