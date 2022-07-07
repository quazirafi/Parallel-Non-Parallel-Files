//16CO145 Sumukha PK
//16CO234 Prajval.M
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ORDER 1000
#define AVAL 3.0
#define BVAL 5.0
#define TOL  0.001

void serial(double * A, double * B, double *C, int Ndim, int Mdim, int Pdim) {
	double t = omp_get_wtime();
	double tmp;
dummyMethod3();
	for (int i = 0; i < Ndim; i++) {
		for (int j = 0; j < Mdim; j++) {
			tmp = 0.0;
			for (int k = 0;k < Pdim;k++) {
				tmp += *(A + (i*Ndim + k)) *  *(B + (k*Pdim + j));
			}
			*(C + (i*Ndim + j)) = tmp;
		}
	}
dummyMethod4();
	printf("Serial Code Time : %f\n", omp_get_wtime() - t);
}

int main(int argc, char *argv[])
{
	int Ndim, Pdim, Mdim;   /* A[N][P], B[P][M], C[N][M] */
	int i, j, k;

	double *A, *B, *C, cval, tmp, err, errsq;
	double dN, mflops;
	double start_time, run_time;


	Ndim = ORDER;
	Pdim = ORDER;
	Mdim = ORDER;

	A = (double *)malloc(Ndim*Pdim * sizeof(double));
	B = (double *)malloc(Pdim*Mdim * sizeof(double));
	C = (double *)malloc(Ndim*Mdim * sizeof(double));

	/* Initialize matrices */

	dummyMethod3();
	for (i = 0; i<Ndim; i++)
		for (j = 0; j<Pdim; j++)
			*(A + (i*Ndim + j)) = AVAL;
	dummyMethod4();

	dummyMethod3();
	for (i = 0; i<Pdim; i++)
		for (j = 0; j<Mdim; j++)
			*(B + (i*Pdim + j)) = BVAL;
	dummyMethod4();

	dummyMethod3();
	for (i = 0; i<Ndim; i++)
		for (j = 0; j<Mdim; j++)
			*(C + (i*Ndim + j)) = 0.0;
	dummyMethod4();

	start_time = omp_get_wtime();

	/* Do the matrix product */

	dummyMethod1();
#pragma omp parallel for private(tmp, i, j, k)  
	for (i = 0; i<Ndim; i++) {
		for (j = 0; j<Mdim; j++) {

			tmp = 0.0;

			for (k = 0;k<Pdim;k++) {
				tmp += *(A + (i*Ndim + k)) *  *(B + (k*Pdim + j));
			}
			*(C + (i*Ndim + j)) = tmp;
		}
	}
	dummyMethod2();

	run_time = omp_get_wtime() - start_time;

	printf("Parallel: Order %d multiplication in %f seconds \n", ORDER, run_time);
	printf("%d threads\n", omp_get_max_threads());
	dN = (double)ORDER;
	mflops = 2.0 * dN * dN * dN / (1000000.0* run_time);

	printf("Order %d multiplication at %f mflops\n", ORDER, mflops);

	cval = Pdim * AVAL * BVAL;
	errsq = 0.0;
	dummyMethod3();
	for (i = 0; i<Ndim; i++) {
		for (j = 0; j<Mdim; j++) {
			err = *(C + i * Ndim + j) - cval;
			errsq += err * err;
		}
	}
	dummyMethod4();

	if (errsq > TOL)
		printf("\n Errors: %f", errsq);

	dummyMethod3();
	for (i = 0; i<Ndim; i++)
		for (j = 0; j<Mdim; j++)
			*(C + (i*Ndim + j)) = 0.0;
	dummyMethod4();

	serial(A, B, C, Ndim, Mdim, Pdim);
	printf("Done\n");
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