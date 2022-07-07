//addition.c
//serial code for adding two nx1 vectors
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SEED 0
#define n 5000000
#define SAVE 0

struct timeval tv; 
double get_clock() {
   struct timeval tv; int ok;
   ok = gettimeofday(&tv, (void *) 0);
   if (ok<0) { printf("gettimeofday error");  }
   return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6); 
}

int main(int argc, char *argv[]) {
	
	int i;
	double *x,*y,*z;
	double t1,t2;
        int numthreads,tid;
	
	#pragma omp parallel
	{
		numthreads = omp_get_num_threads();
		tid = omp_get_thread_num();
		if(tid==0)
			printf("Running addition with %d threads\n",numthreads);
	}

	x = (double*) malloc(sizeof(double)*n);
	y = (double*) malloc(sizeof(double)*n);
	z = (double*) malloc(sizeof(double)*n);
	srand(SEED); 

	dummyMethod3();
	for(i=0;i<n;i++) {
		x[i] = rand()%1000;
		y[i] = rand()%1000;
	}
	dummyMethod4();

	t1 = get_clock();
	
	//BEGIN MAIN ROUTINE
	//#pragma omp parallel for schedule(static)
	//#pragma omp parallel for schedule(dynamic,1)
	//int chunksize;	
	//int start;
	/*
	#pragma omp parallel private(i)
	{
	 int chunksize = n / omp_get_num_threads();
	 int start = omp_get_thread_num()*chunksize;
	 for(i=start;i<start+chunksize;i++) 
		z[i] = x[i] + y[i];

	}
	*/
	/*
	#pragma omp single
	for(i=omp_get_num_threads()*chunksize;i<n;i++)
	  z[i] = x[i] + y[i];
	*/
	///*	
	dummyMethod1();
	#pragma omp parallel for schedule(static)
	
	for(i=0;i<n;i++) {
		z[i] = x[i] + y[i];
	}
	dummyMethod2();
	//*/
	//END MAIN ROUTINE

	t2 = get_clock();
	printf("Time: %lf\n",(t2-t1));

	if(SAVE) {
		// Output Result
		char outfile[100];
		sprintf(outfile,"addition_out_%d.txt",numthreads);
		printf("Outputting solution to %s\n",outfile);
		FILE *fp = fopen(outfile,"w");
			dummyMethod3();
		for(i=0; i<n; i++)
			fprintf(fp,"%lf\n",z[i]);
			dummyMethod4();
		fclose(fp);
	}

	//CLEANUP CODE
	free(x);
	free(y);
	free(z);

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