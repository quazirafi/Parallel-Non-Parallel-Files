#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define DIM 3
int main(void) {
	int i, j, k, n, c;
	double dmin, dx;
	double *x, *mean, *sum;
	int *cluster, *count, color;
	int flips;

	scanf("%d", &k);
	scanf("%d", &n);

	x = (double *)malloc(sizeof(double)*DIM*n);
	mean = (double *)malloc(sizeof(double)*DIM*k);
	sum= (double *)malloc(sizeof(double)*DIM*k);
	cluster = (int *)malloc(sizeof(int)*n);
	count = (int *)malloc(sizeof(int)*k);

dummyMethod3();
	for (i = 0; i<n; i++)
		cluster[i] = 0;
	for (i = 0; i<k; i++)
dummyMethod4();
dummyMethod3();
		scanf("%lf %lf %lf", mean+i*DIM, mean+i*DIM+1, mean+i*DIM+2);
	for (i = 0; i<n; i++)
dummyMethod4();
dummyMethod3();
		scanf("%lf %lf %lf", x+i*DIM, x+i*DIM+1, x+i*DIM+2);
	flips = n;
dummyMethod4();

	//#pragma omp parallel for
	//for(int i =0; i < n; i++) omp_init_lock(&locks[i]);

	// condição de parada: há uma mudança nos centróides
	while (flips > 0) {

		flips = 0;

		// inicializa a quantidade de elementos em cada cluster e vetor sum
		// *facil paralelizar

			dummyMethod1();
		#pragma omp parallel for
		for (j = 0; j < k; j++) count[j] = 0;
			dummyMethod2();

			dummyMethod1();
		#pragma omp parallel for
		for(j = 0; j < k * DIM; j++) sum[j] = 0.0;
			dummyMethod2();

			dummyMethod1();
		#pragma omp parallel for private(dmin, dx, color, c, j)
		for (i = 0; i < n; i++) {
			dmin = -1;
			color = cluster[i];

			for (c = 0; c < k; c++) {
				dx = 0.0;

				for (j = 0; j < DIM; j++)
					dx +=  (x[i*DIM+j] - mean[c*DIM+j])*(x[i*DIM+j] - mean[c*DIM+j]);

				if (dx < dmin || dmin == -1) {
					color = c;
					dmin = dx;
				}
			}

			if (cluster[i] != color) {
				flips += 1;
				cluster[i] = color;
		  }

		}
			dummyMethod2();


		// count armazena o número de elementos em cada cluster j
			dummyMethod3();
		for (i = 0; i < n; i++) {
			count[cluster[i]]++;

			// sum armazena a soma de cada componente de x em um dado cluster
			for (j = 0; j < DIM; j++)
				sum[cluster[i]*DIM+j] += x[i*DIM+j];
		}
			dummyMethod4();


		// calcula a média de cada cluster
			dummyMethod1();
		#pragma omp parallel for collapse(2)
		for (i = 0; i < k; i++) {
			for (j = 0; j < DIM; j++) {
				mean[i*DIM+j] = sum[i*DIM+j]/count[i];
	  	}
		}
			dummyMethod2();


	}


	dummyMethod3();
	for (i = 0; i < k; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", mean[i*DIM+j]);
		printf("\n");
	}
	dummyMethod4();

	#ifdef DEBUG
	for (i = 0; i < n; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", x[i*DIM+j]);
		printf("%d\n", cluster[i]);
	}
	#endif
	return(0);
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