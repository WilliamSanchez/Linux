#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data_demo{
  int a;
  int b;
};

char dataArray[124];

int main()
{

	struct data_demo dataStruct[3];
	
	struct data_demo **dataStructRcv;
	
	dataStruct[0].a = 90;
	dataStruct[0].b = 12;
	
	dataStruct[1].a = 34;
	dataStruct[1].b = 9;
	
	dataStruct[2].a = 68;
	dataStruct[2].b = 2;
	
	printf("Struct \n");
	
	for(int i=0; i < 3; i++){
		printf("[%d|%d]\n", dataStruct[i].a, dataStruct[i].b);
	}
	printf("Array \n");
	
	for(int j=0; j < 3; j++){
		memcpy(dataArray+j*(sizeof(struct data_demo)),&dataStruct[j],sizeof(struct data_demo));
	}
	
	printf("Size of data_demo %d, length of dataArray %d\n", sizeof(struct data_demo), sizeof(dataArray));
	
	int x =0;
	while(x < sizeof(dataArray))
	{
		printf("%x|",dataArray[x]);
		x++;
	}
	
	printf("\nStruct\n");
	
	
	dataStructRcv = (struct data_demo **)calloc(3, sizeof(struct data_demo*));
	dataStructRcv[0] = (struct data_demo *)calloc(1, sizeof(struct data_demo));
	memcpy(dataStructRcv[0], dataArray, sizeof(struct data_demo));
	dataStructRcv[1] = (struct data_demo *)calloc(1, sizeof(struct data_demo));
	memcpy(dataStructRcv[1], dataArray+sizeof(struct data_demo), sizeof(struct data_demo));
	dataStructRcv[2] = (struct data_demo *)calloc(1, sizeof(struct data_demo));
	memcpy(dataStructRcv[2], dataArray+2*sizeof(struct data_demo), sizeof(struct data_demo));
	
	for(int i=0; i < 3; i++){
		printf("[%d|%d]\n", dataStructRcv[i]->a, dataStructRcv[i]->b);
	}

	return 0;
}


