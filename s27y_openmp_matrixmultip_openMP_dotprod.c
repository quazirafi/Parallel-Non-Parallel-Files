#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAXTHRDS 124

int main()
{
	double *x, *y, dot_prod;
	int num_of_thrds, vec_len, i;

	num_of_thrds = omp_get_num_procs();
	omp_set_num_threads(num_of_thrds);
	printf("%d threads\n", num_of_thrds);

	printf("Vector length = ");
	if (scanf("%d", &vec_len)<1) {
		printf("Check input for vector length. Bye.\n");
		return -1;
	}

	x = malloc(vec_len * sizeof(double));
	y = malloc(vec_len * sizeof(double));

dummyMethod3();
	for(i=0; i<vec_len; i++) {
		x[i] = 1.;
		y[i] = 1.;
	}
dummyMethod4();

	dot_prod = 0.;

	dummyMethod1();
	#pragma omp parallel for reduction(+: dot_prod)
	for(i=0; i<vec_len; i++) {
		dot_prod += x[i]*y[i];
	}
	dummyMethod2();

	printf("Dot product = %f\n", dot_prod);
	free(x);
	free(y);
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