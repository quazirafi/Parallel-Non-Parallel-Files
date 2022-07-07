#include <stdio.h>
#include <string.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAXSIZE 8192

int thread = 10;

/* LU: Compute LU factorization of A
 * Upper triangular part of A is overwritten with U
 * Strict lower triangular part of A is overwritten with L
 * L has ones on diagonal, but these are not stored 
 */
void LU(int n, double A[][n])
{
    int i, j, k;
    double pivot;
    for (k = 0; k < n-1; k++) {
        pivot = A[k][k]; 
dummyMethod1();
	#pragma omp parallel for num_threads(thread)
        for (i = k+1; i < n; i++) {
            A[i][k] = A[i][k]/pivot; 
        }
dummyMethod2();
dummyMethod1();
	#pragma omp parallel for collapse(2) num_threads(thread) //proc_bind(close)
        for (i = k+1; i < n; i++) {
            for (j = k+1; j < n; j++) {
                A[i][j] = A[i][j] - A[i][k]*A[k][j];
            }
        }
dummyMethod2();
    }
}

/* solve_U: Solve strict lower triangular system Lx = b 
 * Routine is called with x=b
 * L has ones on diagonal (not stored); 
 * Upper triangle of L is ignored
 */  
void solve_L(int n, double x[], double L[][n])
{
    int i, j;
    for (i = 1; i < n; i++) {
	dummyMethod1();
        #pragma omp parallel for private(j) shared(i) num_threads(thread)
	for (j = i; j < n; j++) {
            x[j] = x[j] - L[j][i-1]*x[i-1];
	} 
	dummyMethod2();
    }
}

/* solve_U: Solve upper triangular system Ux = b 
 * Routine is called with x=b
 * Lower triangle of U is ignored
 */  
void solve_U(int n, double x[], double U[][n])
{
    int i, j;
    for (i = n-1; i > 0; i--) {
	{
        	x[i] = x[i]/U[i][i];
																	dummyMethod1();
        	#pragma omp parallel for num_threads(thread) private(j) shared(i) 
        	for (j = 0; j < i; j++) 
            		x[j] = x[j] - U[j][i]*x[i]; 
																	dummyMethod2();
    
	}
    }
    x[0] = x[0]/U[0][0];
}

/* matvec: Compute y = A*x 
 */
void matvec(int n, double y[], double x[], double A[][n])
{
    int i, j;
       // #pragma omp parallel for private(i,j, x,y) shared(n,A) num_threads(thread)  
    //#pragma omp parallel for shared(n,y,x,A) num_threads(thread)  
    for (i = 0; i < n; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) 
            y[i] = y[i] + A[i][j]*x[j]; 
    }
}

/* saxpy: Compute y = x + alpha * y
 */
void saxpy(int n, double alpha, double y[], double x[]) 
{
    int i; 
							dummyMethod1();
    #pragma omp parallel for num_threads(thread) private(i) 
    for (i = 0; i < n; i++) {
	y[i] = x[i] + alpha*y[i];
    }
							dummyMethod2();
}


/* nrm: Compute 2-norm of x 
 */
double norm(int n, double x[]) 
{
    int i; 
    double sum = 0.0;
    double nrm; 
							dummyMethod1();
    #pragma omp parallel for shared(n) reduction(+:sum) num_threads(thread)
    for (i = 0; i < n; i++) 
	sum = sum + x[i]*x[i]; 
							dummyMethod2();
    return sqrt(sum);
}

void initialize_vector(int n, double x[]) 
{
    int i;
							dummyMethod1();
    #pragma omp parallel for shared(n) num_threads(thread)
    for (i = 0; i < n; i++)
        x[i] = 1.0;
							dummyMethod2();
}

void initialize_matrix(int n, double A[][n]) 
{
    int i, j;
							dummyMethod1();
    #pragma omp parallel for shared(n, A) private(i) num_threads(thread)
    for (i = 0; i < n; i++) 
							dummyMethod2();
    	#pragma omp parallel for shared(n, A) private(j) num_threads(thread)
        for (j = 0; j < n; j++) 
            A[i][j] = 1.0/(1.0+abs(i-j)); 
}
main(int argc, char **argv)
{
    double nrm; 
    enum timer {tinit, tLU, tsolve_L, tsolve_U, tmatvec, tsaxpy, tnorm};
    double start, timing[tnorm+1];
    double A[MAXSIZE][MAXSIZE], A0[MAXSIZE][MAXSIZE];
    double x[MAXSIZE], b[MAXSIZE], y[MAXSIZE];
    int n;
    /* Check input parameters */
    n = atoi(argv[1]); 
    thread = atoi(argv[2]); 

    if (n > MAXSIZE) {
        printf("n must be less than %d ... aborting\n", MAXSIZE); 
        exit(0); 
    }
    if (n <= 0) {
        printf("n must be a positive integer ... aborting\n"); 
        exit(0); 
    }
	
    start = omp_get_wtime();    /* Start timing */
    initialize_matrix(n, A);    /* Initialize matrix */
    initialize_matrix(n, A0);   /* Copy A in A0 */

    initialize_vector(n, b);    /* Initialize vector */
    initialize_vector(n, x);    /* Copy b in x */
    timing[tinit] = omp_get_wtime() - start; 
//printf("%s\n", "Here");
    start = omp_get_wtime();    /* Start timing */
    LU(n, A);                   /* LU factorization */
    timing[tLU] = omp_get_wtime() - start; 

    start = omp_get_wtime();    /* Start timing */
    solve_L(n, x, A);           /* Compute x = inv(L)x */
    timing[tsolve_L] = omp_get_wtime() - start; 

    start = omp_get_wtime();    /* Start timing */
    solve_U(n, x, A);           /* Compute x = inv(L)x */
    timing[tsolve_U] = omp_get_wtime() - start; 

    start = omp_get_wtime();    /* Start timing */
    matvec(n, y, x, A0);        /* Check solution: y = A*x */
    timing[tmatvec] = omp_get_wtime() - start; 

    start = omp_get_wtime();    /* Start timing */
    saxpy(n, -1.0, y, b);       /* Check solution: y = b - y */
    timing[tsaxpy] = omp_get_wtime() - start; 

    start = omp_get_wtime();    /* Start timing */
    nrm = norm(n, y);           /* Check solution: nrm = ||y|| */
    timing[tnorm] = omp_get_wtime() - start; 

    printf("Residual norm: ||b-Ax|| = %e\n", nrm); 
    printf("Size - n:       %10d\n", n); 
    printf("Time - init:    %10.4e\n", timing[tinit]); 
    printf("Time - LU:      %10.4e\n", timing[tLU]); 
    printf("Time - solve_L: %10.4e\n", timing[tsolve_L]); 
    printf("Time - solve_U: %10.4e\n", timing[tsolve_U]); 
    printf("Time - matvec:  %10.4e\n", timing[tmatvec]); 
    printf("Time - saxpy:   %10.4e\n", timing[tsaxpy]); 
    printf("Time - norm:    %10.4e\n", timing[tnorm]); 
/*
    printf("%10.4e %10.4e %10.4e %10.4e %10.4e %10.4e %12.2e\n", 
            timing[tLU], timing[tsolve_L], timing[tsolve_U], 
            timing[tmatvec], timing[tsaxpy], timing[tnorm], 
            nrm); 
*/
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