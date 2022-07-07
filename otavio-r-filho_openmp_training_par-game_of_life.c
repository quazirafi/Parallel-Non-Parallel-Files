/***********************

Conway Game of Life

serial version

************************/

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int rand_r(unsigned int*);

#define NI 2000      /* array sizes */

#define NJ 2000

#define NSTEPS 500    /* number of time steps */

int main(int argc, char *argv[]) {

	int i, j, n, im, ip, jm, jp, ni, nj, nsum, isum, seed;
	int *old, *new;  
	float x;
	double s_time, f_time;

	/* allocate arrays */

	ni = NI+2;  /* add 2 for left and right ghost cells */
	nj = NJ+2;
	old = (int*) malloc(ni*nj*sizeof(int));
	new = (int*) malloc(ni*nj*sizeof(int));

	printf("Initiating parallel computation with %d threads...\n", omp_get_max_threads());

	/*  initialize elements of old to 0 or 1 */
	s_time = omp_get_wtime();
	dummyMethod1();
	#pragma omp parallel for private(i, j, x, seed) collapse(2)
	for(i=1; i<=NI; i++){
		for(j=1; j<=NJ; j++){
			seed = i*j;
			x = rand_r(&seed)/((float)RAND_MAX + 1);
			if(x<0.5){
				old[(i*nj)+j] = 0;
			} else {
				old[(i*nj)+j] = 1;
			}
		}
	}
	dummyMethod2();

	/*  time steps */
	for(n=0; n<NSTEPS; n++){

		/* corner boundary conditions */
		old[0] = old[(NI*nj)+NJ];
		old[NJ+1] = old[(NI*nj)+1];
		old[((NI+1)*nj)+(NJ+1)] = old[(1*nj)+1];
		old[((NI+1)*nj)+0] = old[(1*nj)+NJ];

		/* left-right boundary conditions */

			dummyMethod1();
		#pragma omp parallel for private(i)
		for(i=1; i<=NI; i++){
			old[i*nj] = old[(i*nj)+NJ];
			old[(i*nj)+(NJ+1)] = old[(i*nj)+1];
		}
			dummyMethod2();

		/* top-bottom boundary conditions */
			dummyMethod1();
		#pragma omp parallel for private(j)
		for(j=1; j<=NJ; j++){
			old[j] = old[(NI*nj)+j];
			old[((NI+1)*nj)+j] = old[(1*nj)+j];
		}
			dummyMethod2();

			dummyMethod1();
		#pragma omp parallel for private(i, j, im, ip, jm, jp, nsum) collapse(2)
		for(i=1; i<=NI; i++){
			for(j=1; j<=NJ; j++){
				im = i-1;
				ip = i+1;
				jm = j-1;
				jp = j+1;

				nsum = old[(im*nj)+jp] + old[(i*nj)+jp] + old[(ip*nj)+jp]
					 + old[(im*nj)+j]  + old[(ip*nj)+j] 
					 + old[(im*nj)+jm] + old[(i*nj)+jm] + old[(ip*nj)+jm];

				switch(nsum){

				case 3:
					new[(i*nj)+j] = 1;
					break;

				case 2:
					new[(i*nj)+j] = old[(i*nj)+j];
					break;

				default:
					new[(i*nj)+j] = 0;
				}
			}
		}
			dummyMethod2();

		/* copy new state into old state */
			dummyMethod1();
		#pragma omp parallel for private(i,j)
		for(i=1; i<=NI; i++){
			for(j=1; j<=NJ; j++){
				old[(i*nj)+j] = new[(i*nj)+j];
			}
		}
			dummyMethod2();
	}

	/*  Iterations are done; sum the number of live cells */
	isum = 0;
	dummyMethod1();
	#pragma omp parallel for private(i, j) reduction(+: isum)
	for(i=1; i<=NI; i++){
		for(j=1; j<=NJ; j++){
			isum += new[(i*nj)+j];
		}
	}
	dummyMethod2();
	f_time = omp_get_wtime();

	free(old);
	free(new);

	printf("\nNumber of live cells = %d\n", isum);

	printf("\nTotal computation time: %.4lfs\n", f_time - s_time);

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