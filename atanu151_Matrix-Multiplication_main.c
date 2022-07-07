//Large Matrix Multiplication
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define m 2048 //rows of Matrix A & Matrix C || rows and columns of square Matrix(D,E,F,G)
#define n 2048 //columns of Matrix A & rows of Matrix B
#define o 2048 //columns of Matrix B & Matrix C

#define MIN(a,b) (((a)<(b))?(a):(b)) //returns the minimum of the two variables (used in blocking method)

#define bsize 64 //block size

#define SEED 0

//function for getting the time
struct timeval tv;
double get_time() {
   struct timeval tv;
   int ok;
   ok = gettimeofday(&tv, (void *) 0);
   if (ok<0)
    {
        printf("error in getting the time");
    }
   return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6);
}

//Random Non-square Matrix A creation
double **create_matrixA() {
	int i,j;
	double **a;

	a = (double**) malloc(sizeof(double*)*m);
	dummyMethod3();
	for (i=0;i<m;i++)
        {
		a[i] = (double*) malloc(sizeof(double)*m);
        }
	dummyMethod4();

	srand(SEED);
	dummyMethod3();
	for (i=0;i<m;i++)
        {
		for (j=0;j<n;j++)
		{
			a[i][j] = rand()%10;
		}
	}
	dummyMethod4();

	return a;
}

//Random Non-square Matrix B creation
double **create_matrixB() {
	int i,j;
	double **a;

	a = (double**) malloc(sizeof(double*)*n);
	dummyMethod3();
	for (i=0;i<n;i++)
        {
		a[i] = (double*) malloc(sizeof(double)*n);
        }
	dummyMethod4();

	srand(SEED);
	dummyMethod3();
	for (i=0;i<n;i++)
        {
		for (j=0;j<o;j++)
		{
			a[i][j] = rand()%10;
		}
	}
	dummyMethod4();

	return a;
}

//Random Square Matrix creation D, E
double **create_matrixS() {
	int i,j;
	double **a;

	a = (double**) malloc(sizeof(double*)*m);
	dummyMethod3();
	for (i=0;i<m;i++) {
		a[i] = (double*) malloc(sizeof(double)*m);
	}
	dummyMethod4();

	srand(SEED);
	dummyMethod3();
	for (i=0;i<m;i++) {
		for (j=0;j<m;j++) {
			a[i][j] = rand()%10;
		}
	}
	dummyMethod4();

	return a;
}

//deallocating the memory of the Matrix
void free_matrix(double **a) {
	free(a);
}


int main(int argc, char *argv[]) {

	int i,j,k,ii,jj,kk;
	double sum;
	double **A, **B, **C, **D, **E, **F, **G;
	double st,et;

	//checking the number of threads available
	int numthreads,tid;
        #pragma omp parallel
        {
                numthreads = omp_get_num_threads();
                tid = omp_get_thread_num();
                if(tid==0)
                {
                        printf("Executing Matrix multiplication with %d threads\n",numthreads);
                }
        }

	//**************************************<METHOD-1>****************************************

	D = create_matrixS();

	E = create_matrixS();

    // F is the resulting matrix of D*E
	F = (double**) malloc(sizeof(double*)*m);
							dummyMethod3();
    for (i=0;i<m;i++) {
        F[i] = (double*) malloc(sizeof(double)*m);
    }
							dummyMethod4();
	dummyMethod3();
	for(i=0; i<m; i++) {
		for(j=0; j<m; j++)
        {
			F[i][j] = 0.0;
        }
	}
	dummyMethod4();

	//G is used to store the transpose of Matrix E
	G = (double**) malloc(sizeof(double*)*m);
							dummyMethod3();
    for (i=0;i<m;i++) {
        G[i] = (double*) malloc(sizeof(double)*m);
    }
							dummyMethod4();
	dummyMethod3();
	for(i=0; i<m; i++) {
		for(j=0; j<m; j++)
        {
			G[i][j] = 0.0;
        }
	}
	dummyMethod4();

	//Transpose Method for Multiplication
	st = get_time();
	// Transpose of Matrix E stored in Matrix G
	dummyMethod3();
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			G[j][i] = E[i][j];
		}
	}
	dummyMethod4();
	dummyMethod1();
	#pragma omp parallel for private(j,k, sum)
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			sum = 0.0;
			for (k = 0; k < m; k++) {
				sum += D[i][k] * G[j][k];
			}
			F[i][j] = sum;
		}
	}
	dummyMethod2();
    et = get_time();
	//printf("Time using Transpose Method (Square Matrix): %lf\n",(t2-t1));
    printf("Method 1 - Transpose Method (Square Matrix): %lf\n",(et-st));

    // Concurrent Matrix multiplication without Transpose Method
    /*
    for(i=0; i<m; i++) {
		for(j=0; j<m; j++)
        {
			F[i][j] = 0.0;
        }
	}
	st = get_clock();
	#pragma omp parallel for private(j,k, sum)
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			sum = 0.0;
			for (k = 0; k < m; k++) {
				sum += D[i][k] * E[k][j];
			}
			F[i][j] = sum;
		}
	}
    et = get_clock();
	printf("Time without using Transpose Method (Square Matrix): %lf\n",(et-st)); */


    //**************************************<METHOD-2>****************************************
	A = create_matrixA();

    B = create_matrixB();

    //C is the resulting matrix of A*B
	C = (double**) malloc(sizeof(double*)*m);
							dummyMethod3();
    for (i=0;i<m;i++) {
        C[i] = (double*) malloc(sizeof(double)*m);
    }
							dummyMethod4();

							dummyMethod3();
    for(i=0; i<m; i++) {
		for(j=0; j<o; j++)
        {
			C[i][j] = 0.0;
        }
	}
							dummyMethod4();

	st = get_time();
	dummyMethod1();
	#pragma omp parallel for private(kk,i,j,k,sum)
	//#pragma omp parallel for private(jj,kk,i,j,k,sum) collapse(3)
	for (jj = 0; jj<o; jj+=bsize) {
        for (kk = 0; kk<n; kk+=bsize) {
            for(i = 0; i<m; i++) {
	//#pragma omp parallel for private(j,k,sum)
	//#pragma omp parallel for private(j,k) collapse(3)
                for (j = jj; j < MIN(jj+bsize,o); j++) {
               // for (k = kk; k < MIN(kk+bsize,n); k++) {
               // for (j = jj; j < MIN(jj+bsize,n); j++) {
                        sum = 0.0;
                //#pragma omp parallel for reduction(+:C[:i][:j])
                    //#pragma omp critical
                    for (k = kk; k < MIN(kk+bsize,n); k++) {
                   // for (j = jj; j < MIN(jj+bsize,o); j++) {
                        sum += A[i][k] * B[k][j];
                    }
                    C[i][j] += sum;
	       // }
                }
            }
        }
    }
	dummyMethod2();

	et = get_time();
	printf("Method 2 - Blocking (jj-kk-i-j-k) : %lf\n",(et-st));

	//**************************************<METHOD-3>****************************************

	//initializing resulting matrix C for A*B
	dummyMethod3();
	for(i=0; i<m; i++) {
		for(j=0; j<o; j++)
        {
			C[i][j] = 0.0;
        }
	}
	dummyMethod4();

	st = get_time();
	dummyMethod1();
	#pragma omp parallel for private(jj,kk,i,j,k,sum)
	//#pragma omp parallel for private(jj,kk,i,j,k,sum) collapse(3)
	for (ii = 0; ii<m; ii+=bsize) {
          for (jj = 0; jj<o; jj+=bsize) {
	    for(kk = 0; kk<n; kk+=bsize) {
	//#pragma omp parallel for private(j,k,sum)
	//#pragma omp parallel for private(j,k) collapse(3)
              for (i = ii; i < MIN(ii+bsize,m); i++) {
                for (j = jj; j < MIN(jj+bsize,o); j++) {
		  sum = 0.0;
		  //#pragma omp parallel for reduction(+:sum)
                  for (k = kk; k < MIN(kk+bsize,n); k++) {
                    sum += A[i][k] * B[k][j];
                  }
		  C[i][j]+= sum;
	        }
              }
            }
          }
        }
	dummyMethod2();

	et = get_time();
	printf("Method 3 - Blocking (ii-jj-kk-i-j-k) : %lf\n",(et-st));


    //**************************************<Simple-Matrix-Multiplication>*******************************

    //initializing resulting matrix C for A*B
	dummyMethod3();
	for(i=0; i<m; i++) {
		for(j=0; j<o; j++)
        {
			C[i][j] = 0.0;
        }
	}
	dummyMethod4();

	st = get_time();
	dummyMethod3();
	for (i = 0; i < m; i++) {
		for (j = 0; j < o; j++) {
            sum = 0.0;
			for (k = 0; k < n; k++) {
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}
	}
	dummyMethod4();

    et = get_time();
	printf("Simple Matrix Multiplication: %lf\n",(et-st));


	//Free allocated Matrix spaces
	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	free_matrix(D);
	free_matrix(E);
	free_matrix(F);
	free_matrix(G);
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