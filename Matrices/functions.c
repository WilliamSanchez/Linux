#include <functions.h>

#include <math.h>

Matrix euler2DCM(double *euler, Matrix DCM)
{

    double cPHI,sPHI,cTHE,sTHE,cPSI,sPSI;
    
    cPHI = cos(euler[0]); sPHI = sin(euler[0]);
    cTHE = cos(euler[1]); sTHE = sin(euler[1]);
    cPSI = cos(euler[2]); sPSI = sin(euler[2]); 

    DCM.data[0][0]= cTHE*cPSI; 			DCM.data[0][1]= cTHE*sPSI; 			DCM.data[2][0]= -sTHE;
    DCM.data[1][0]= sPHI*sTHE*cPSI-cPHI*sPSI;	DCM.data[1][1]= sPHI*sTHE*sPSI+cPHI*cPSI;	DCM.data[2][1]= sPHI*cTHE;
    DCM.data[2][0]= cPHI*sTHE*cPSI+sPHI*sPSI;	DCM.data[2][1]= cPHI*sTHE*sPSI-sPHI*cPSI;	DCM.data[2][2]= cPHI*cTHE;

    return DCM;
}


Matrix quat2DCM(double *quat, Matrix DCM)
{
   
    double q1,q2,q3,q4;
   
    q1 = quat[0]; q2 = quat[1];  q3 = quat[2];  q4 = quat[3]; 
   
    DCM.data[0][0]= q1*q1+q2*q2-q3*q3-q4*q4;	DCM.data[0][1]= 2*(q1*q3-q2*q4);		DCM.data[2][0]= 2*(q1*q3+q2*q4);
    DCM.data[1][0]= 2*(q2*q3+q1*q4);		DCM.data[1][1]= q1*q1-q2*q2+q3*q3-q4*q4;	DCM.data[2][1]= 2*(q3*q4-q1*q2);
    DCM.data[2][0]= 2*(q2*q4-q1*q3);		DCM.data[2][1]= 2*(q1*q2+q3*q4);		DCM.data[2][2]= q1*q1-q2*q2-q3*q3+q4*q4;
   
   return (DCM);
}


double DCM2quat(Matrix DCM, double *quat)
{
   double q1,q2,q3,q4;
   q1 = 0.5*sqrt(1+DCM.data[0][0]+DCM.data[1][1]+DCM.data[2][2]);
   q2 = (DCM.data[2][1]-DCM.data[1][2])/(4*q1);
   q3 = (DCM.data[0][2]-DCM.data[2][0])/(4*q1);
   q4 = (DCM.data[1][0]-DCM.data[0][1])/(4*q1);
   
   quat[0]=q1; quat[1]=q2; quat[2]=q3; quat[3]=q4;
   
   return (*quat);
}

double euler2quat(double *euler, double *quat)
{

    double roll, pitch, yaw;
    
    roll = euler[0]; pitch = euler[1]; yaw = euler[2];

    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);

    quat[0] = cr * cp * cy + sr * sp * sy;
    quat[1] = sr * cp * cy - cr * sp * sy;
    quat[2] = cr * sp * cy + sr * cp * sy;
    quat[3] = cr * cp * sy - sr * sp * cy;

    return (*quat);
}

double quat2euler(double *quat, double *euler)
{

    double roll, pitch, yaw;
    double q1,q2,q3,q4;
    double M23, M33, M13, M12, M11;
    
    q1 = quat[0]; q2 = quat[1];  q3 = quat[2];  q4 = quat[3];

/*    
    M23 = 2*q3*q4 + 2*q1*q2; 		//2*(q1*q3+q2*q4);
    M33 = 2*q1*q1 + 2*q4*q4 -1 ;	//q1*q1-q2*q2-q3*q3+q4*q4;
    M13 = 2*q2*q4 - 2*q1*q3;		//2*(q3*q4-q1*q2);
    M12 = 2*q2*q3 + 2*q1*q4;		//2*(q2*q3-q1*q4);
    M11 = 2*q1*q1 + 2*q2*q2-1;		//q1*q1+q2+q2-q3*q3-q4*q4;

*/


    M23 = 2*(q1*q3+q2*q4);
    M33 = q1*q1-q2*q2-q3*q3+q4*q4;
    M13 = 2*(q3*q4-q1*q2);
    M12 = 2*(q2*q3-q1*q4);
    M11 = q1*q1+q2+q2-q3*q3-q4*q4;

   roll=atan2(M23,M33);
   pitch = atan2(-M13,sqrt(1-M13*M13));
   yaw = atan2(M12,M11);

    euler[0]=roll; euler[1]=pitch; euler[2]=yaw;

    return (*euler);
}
