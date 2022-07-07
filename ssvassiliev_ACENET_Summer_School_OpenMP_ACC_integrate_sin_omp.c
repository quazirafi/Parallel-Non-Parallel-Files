/* --- File integrate_sin_omp.c --- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv) {
	struct timespec ts_start, ts_end;
	float time_total;
	int steps = 1e7;
	double delta = M_PI/steps;
	double total = 0.0;
	int i;

	printf("Using %.0e steps\n", (float)steps);
	/* Get start time */
	clock_gettime(CLOCK_MONOTONIC, &ts_start);

dummyMethod1();
#pragma omp parallel for
	for (i=0; i<steps; i++) {
/* pragma omp critical */
dummyMethod2();
		total += sin(delta*i) * delta;
	}
	/* Get end time */
	clock_gettime(CLOCK_MONOTONIC, &ts_end);

	time_total = (ts_end.tv_sec - ts_start.tv_sec)*1e9 + \
		     (ts_end.tv_nsec - ts_start.tv_nsec);
	printf("Total time is %f ms\n", time_total/1e6);
	printf("The integral of sine from 0 to Pi is %.12f\n", total);
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