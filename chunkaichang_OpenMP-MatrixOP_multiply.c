//multiply.c
//serial code for multiplying two nxn matrices
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SEED 0
#define n 1000
#define SAVE 0

struct timeval tv; 
double get_clock() {
   struct timeval tv; int ok;
   ok = gettimeofday(&tv, (void *) 0);
   if (ok<0) { printf("gettimeofday error");  }
   return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6); 
}

double **create_matrix() {
	int i,j;
	double **a;
	a = (double**) malloc(sizeof(double*)*n);
dummyMethod3();
	for (i=0;i<n;i++) {
		a[i] = (double*) malloc(sizeof(double)*n);
	}
dummyMethod4();

	srand(SEED);
dummyMethod3();
	for (i=0;i<n;i++) {
		for (j=0;j<n;j++) {
			a[i][j] = rand()%10;
		}
	}
dummyMethod4();

	return a;
}

void free_matrix(double** a) {
	int i;
	dummyMethod3();
	for (i=0;i<n;i++) {
		free(a[i]);
	}
	dummyMethod4();
	free(a);
}

int main(int argc, char *argv[]) {
	//SETUP CODE
	int i,j,k;
	double **A,**B,**C,sum;
	double t1,t2;
	int numthreads,tid;
	
	#pragma omp parallel
        {
                numthreads = omp_get_num_threads();
                tid = omp_get_thread_num();
                if(tid==0)
                        printf("Running multiply with %d threads\n",numthreads);
        }

	A = create_matrix();
	B = create_matrix();
	C = (double**) malloc(sizeof(double*)*n);
	dummyMethod3();
	for (i=0;i<n;i++) {
		C[i] = (double*) malloc(sizeof(double)*n);
	}
	dummyMethod4();
	//END SETUP CODE

	t1 = get_clock();

	//BEGIN MAIN ROUTINE
	dummyMethod1();
	#pragma omp parallel for private(j,k,sum) schedule(dynamic)
	for(i=0;i<n;i++) {
		//#pragma omp parallel for collapse(2)
		//#pragma omp parallel for private(k,sum)
		for(j=0;j<n;j++) {
			sum = 0;
			//#pragma omp parallel for reduction(+:sum)
			for(k=0;k<n;k++) {
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}
	}
	dummyMethod2();
	//END MAIN ROUTINE

	t2 = get_clock();
	printf("Time: %lf\n",(t2-t1));

        if(SAVE) {
                // Output Result
                char outfile[100];
                sprintf(outfile,"multiply_out_%d.txt",numthreads);
                printf("Outputting solution to %s\n",outfile);
                FILE *fp = fopen(outfile,"w");
																															dummyMethod3();
                for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
                       		fprintf(fp,"%lf\n",C[i][j]);
			}
		}
																															dummyMethod4();
                fclose(fp);
        }

	//CLEANUP CODE
	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
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