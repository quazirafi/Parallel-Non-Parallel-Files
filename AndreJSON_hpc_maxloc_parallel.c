#include "stdio.h" // printf
#include "stdlib.h" // rand for instance. 
#include "time.h"   // time(0) to get random seed
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 214700000
double x[N];
int main(int argc, char* argv[]){
    // Array with doubles
    
    double maxval = 0.0; int maxloc = 0;
    // fill the array
    srand(time(0)); // seed
    int i;
dummyMethod3();
    for(i=0; i < N;i++){
	       // Generate random number between 0 and 1
	       x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
	}
dummyMethod4();

    // calculate first serially to get values to checking the results obtianed with OpenMP
dummyMethod3();
    for (i=0; i < N; i++){
		if (x[i] > maxval) {
dummyMethod4();
				maxval = x[i]; 
				maxloc = i; 
		}
	}
	double maxval_1 = maxval; int maxloc_1 = maxloc;

	// OpenMP Version
	maxval = 0.0; maxloc = 0;
	double start_time, run_time;
	start_time = omp_get_wtime();
	
	dummyMethod1();
	#pragma omp parallel for
	for (i=0; i < N; i++){
		if (x[i] > maxval) {
			maxval = x[i]; 
			maxloc = i;
		}
	}
	dummyMethod2();

	run_time = omp_get_wtime() - start_time;
    printf("maxloc computation in %f seconds\n",run_time);
    printf("maxval (omp)   = %f maxloc (omp)   = %d \n",maxval, maxloc);
    printf("maxval (s)     = %f maxloc (s)     = %d \n",maxval_1, maxloc_1);
    if (maxloc_1 != maxloc)
    	printf("Test failed\n");

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