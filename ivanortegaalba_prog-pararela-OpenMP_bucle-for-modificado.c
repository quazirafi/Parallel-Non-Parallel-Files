#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char **argv) {
	int i, n = 9;
	if(argc < 2) {
		fprintf(stderr,"\n[ERROR] - Falta no iteraciones \n");
		exit(-1);
	}
	n = atoi(argv[1]);
dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<n; i++)
		printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(), i);
	return(0);
dummyMethod2();
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