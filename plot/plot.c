#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

  	//FILE *pipe_gp = popen("gnuplot","w");
	FILE *pipe = fopen("plot.dat","w");
  
  	//fputs("set terminal png \n", pipe_gp);
  	//fputs("plot '-' u 1:2 \n",pipe_gp);

	int i;
	for (i=0; i<100000; i++){
		double x = i/100.0;
		//fprintf(pipe_gp,"%f %f \n", x, x*x);
		sleep(1);
		fprintf(pipe,"%f %f \n", x, x*x);
		
	}

	//fputs("e\n",pipe_gp);
	//pclose(pipe_gp);
	fclose(pipe);

	return 0;
}
