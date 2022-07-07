//transpose.c
//serial code for transposing a matrix in-place
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SEED 0
#define n 5000
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

void free_matrix(double **a) {
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
	int i,j;
	double **A;
	double t1,t2,temp;
	int numthreads,tid;

        #pragma omp parallel
        {
                numthreads = omp_get_num_threads();
                tid = omp_get_thread_num();
                if(tid==0)
                        printf("Running transpose with %d threads\n",numthreads);
        }

	A = create_matrix();

	t1 = get_clock();

	//BEGIN MAIN ROUTINE
	//i = 0;
	//#pragma omp parallel for firstprivate(j) private(temp) collapse(2)
	//#pragma omp parallel for private(j,temp)
	for(i=0;i<n;i++) {
			dummyMethod1();
		#pragma omp parallel for private(temp)
		for(j=i+1;j<n;j++) {
			temp=A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = temp;
		}
			dummyMethod2();
	}
	//END MAIN ROUTINE

	t2 = get_clock();
	printf("Time: %lf\n",(t2-t1));

	if(SAVE) {
                // Output Result
                char outfile[100];
                sprintf(outfile,"transpose_out_%d.txt",numthreads);
                printf("Outputting solution to %s\n",outfile);
                FILE *fp = fopen(outfile,"w");
                for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
                        	fprintf(fp,"%lf\n",A[i][j]);
			}
		}
                fclose(fp);
        }

	//CLEANUP CODE
	free_matrix(A);
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