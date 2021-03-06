#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#include <stdint.h>
//#include <math.h>
//#include<sys/types.h>

#define OPENMP_MODE
#ifdef OPENMP_MODE
#include "omp.h"
  #define PROGRESSBAR_MT
  #define NTHREADS 2
#else
  #define NTHREADS 1
#endif


#define N (uint64_t)1E9
#define pbar double
#define workspace_t int
int main(){
	uint64_t i;
	workspace_t w[NTHREADS];
	double y, z;
	uint64_t pi=0;
	pbar barra;
	char* filename="reso.log";

dummyMethod3();
	for(i=0;i<NTHREADS;i++){
		SetRandomSeed(w+i);
	}
dummyMethod4();
	//printf("Workspaces: %p - %p\n", (void*)w, (void*)(w+1));
	pbar_init(&barra, filename, N, 20, NTHREADS, '|');
	if (barra.err!=0){
		return -1;
	}

	#ifdef OPENMP_MODE
	dummyMethod1();
 	#pragma omp parallel for num_threads(NTHREADS) private(i, y, z) reduction(+:pi)
	#endif
	for(i=0;i<N;i++){
		#ifdef OPENMP_MODE
		workspace_t* W=w+omp_get_thread_num();
		#else
		workspace_t* W=w;
		#endif
		y = RSUnif(W, 0., 1.);
		z = RSUnif(W, 0., 1.);
		//printf("Thread %d - %lu - %p - %p\n", omp_get_thread_num(), i, (void*)w, (void*)W);
		if((y*y + z*z) < 1){
			pi++;
		}
		//fprintf(stderr, "%lu\r", i);
		//barra.i=i;
		//pbar_draw(&barra);
		//if(i*100/(N-1)==barra.perc+1){
			//printf("i= %lu\t", i);
			pbar_draw(&barra, i);
		//}
	}
	dummyMethod2();
	printf("pi = %.16le\n", (double)pi*4/N);

	printf("err=%u\n", barra.err);

	pbar_close(&barra);

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