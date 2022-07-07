#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "omp.h"
#include "utils.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DIM 3


void data_rearrangement(float *Y, float *X, 
			unsigned int *permutation_vector, 
			int N){
	  omp_set_num_threads(NUM_OF_THREADS);
dummyMethod1();
    #pragma omp parallel for
	for(int i=0; i<N; i++){
    memcpy(&Y[i*DIM], &X[permutation_vector[i]*DIM], DIM*sizeof(float));
  }

}
dummyMethod2();
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