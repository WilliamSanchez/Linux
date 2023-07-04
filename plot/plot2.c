#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int arg, char *argv[]){

	FILE *gp = popen("gnuplot","w");
	
	fputs("set terminal png \n", gp);
  	fputs("plot '-' u 1:2 \n", gp);

	int i;
	//fprintf(gp, "plot '-' with lines \n");

	for(i=0; i<10000; i++){
		fprintf(gp,"%i %i \n",i,i+3);
		fflush(gp);
		}
		fprintf(gp,"e\n");
	
	return 0;

}
