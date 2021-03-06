// A Dynamic Programming based solution for 0-1 Knapsack problem
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

// Returns the maximum value that can be put in a knapsack of capacity W
static int knapSack(long int W, long int N, int wt[], int val[])
{
	int *K = (int*) malloc((W+1)*sizeof(int));
	int *Kp = (int*) malloc((W+1)*sizeof(int));
	long int i, w;

	for (i = 0; i <= N; i++)
	{
dummyMethod1();
		#pragma omp parallel for
		for (w = 0; w <= W; w++)
		{
			if (i==0 || w==0)
				K[w] = 0;
			else if (wt[i-1] <= w)
				K[w] = max(val[i-1] + Kp[w-wt[i-1]], Kp[w]);
			else
				K[w] = Kp[w];
		}
dummyMethod2();
		int *tmp = Kp;
		Kp = K;
		K = tmp;
	}

	int result = K[W];

	free(K);
	free(Kp);

	return result;
}

int main(int argc, char **argv){

	FILE *test_file;

	int *val, *wt;   // width and cost values
	long int Nitems; // Number of items
	long int Width;  // Max. load to carry
	long int cont;    // counter
	double tpivot1=0,tpivot2=0,tpivot3=0; //time counting
	struct timeval tim;

	if (argc < 2) {
		printf("Usage: ./%s <test_file> [numer_of_threads]\n", argv[0]);
		return 1;
	}

	if (argc == 3) {
		omp_set_num_threads(atoi(argv[2]));
	}

	//Capture first token time - init execution
	gettimeofday(&tim, NULL);
	tpivot1 = tim.tv_sec+(tim.tv_usec/1000000.0);

	if (!(test_file=fopen(argv[1],"r"))) {
		printf("Error opening Value file: %s\n",argv[1]);
		return 1;
	}

	//Reading number of items and Maximum width
	fscanf(test_file,"%ld %ld\n",&Nitems, &Width);

	val = (int *)malloc(Nitems*sizeof(int)); //values for each element
	wt = (int *)malloc(Nitems*sizeof(int)); //width  for each element

	//Reading value and width for each element
	for (cont=0;cont<Nitems;cont++){
		fscanf(test_file,"%d,%d\n",&val[cont],&wt[cont]);
	}

	gettimeofday(&tim, NULL);
	tpivot2 = (tim.tv_sec+(tim.tv_usec/1000000.0));
	printf("%ld:%ld:%d", Width, Nitems, knapSack(Width,Nitems, wt, val));
	gettimeofday(&tim, NULL);
	tpivot3 = (tim.tv_sec+(tim.tv_usec/1000000.0));
	printf(":%.6lf:%.6lf\n", tpivot3-tpivot2,tpivot3-tpivot1);

	free(val);
	free(wt);

	fclose(test_file);

	return 0;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}