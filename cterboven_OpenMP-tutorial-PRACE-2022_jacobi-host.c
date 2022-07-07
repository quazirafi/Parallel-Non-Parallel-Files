/****************************************************
* Jacobi Solver with OpenACC
*               transformed to OpenMP
* ---------------------------------------------------
* Authors: Sandra Wienke, RWTH Aachen University
*          Jiri Kraus,    NVIDIA Corporation
*          Christian Terboven, RWTH Aachen University
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char** argv)
{
    int i,j;
    int n = 16384;
    int m = 16384;
    int iter_max = 100;
    int nthreads = 0;

    const double pi = 2.0 * asin(1.0);
    const double tol = 1.0e-5;
    double err = 1.0;

    double* restrict const A    = malloc( n*m * sizeof(double) );
    double* restrict const Anew = malloc( n*m * sizeof(double) );
    double* restrict const y0   = malloc( n   * sizeof(double) );

    #pragma omp parallel
    #pragma omp single
    {
        nthreads = omp_get_num_threads();
    }

							dummyMethod1();
    #pragma omp parallel for collapse(2)
    for( j = 0; j < n; j++)
    {
        for( i = 0; i < m; i++ )
        {
            Anew[j *m+ i] = 0.0;
            A[j *m+ i]    = 0.0;
        }
    }
							dummyMethod2();

    // set boundary conditions
							dummyMethod3();
    for (i = 0; i < m; i++)
    {
        A[0     *m+ i] = 0.0;
        A[(n-1) *m+ i] = 0.0;
    }
							dummyMethod4();

							dummyMethod3();
    for (j = 0; j < n; j++)
    {
        y0[j] = sin(pi * j / (n-1));
        A[j *m+ 0] = y0[j];
        A[j *m+ (m-1)] = y0[j]*exp(-pi);
        Anew[j *m+ 0] = A[j *m+ 0];
        Anew[j *m+ (m-1)] = A[j *m+ (m-1)];
    }
							dummyMethod4();

    printf("Jacobi relaxation Calculation: %d x %d mesh with %d threads and at most %d iterations."
           " %d rows out of %d on CPU.\n", n, m, nthreads, iter_max, 0, n);

    double starttime = omp_get_wtime();
    int iter = 0;


    while ( err > tol && iter < iter_max ) {

        err = 0.0;

															dummyMethod1();
        #pragma omp parallel for reduction(max:err) collapse(2)
        for( j = 1; j < n-1; j++) {
            for( i = 1; i < m-1; i++ ) {
                Anew[j *m+ i] = 0.25 * ( A[j     *m+ (i+1)] + A[j     *m+ (i-1)]
                                     +   A[(j-1) *m+ i]     + A[(j+1) *m+ i]);
                err = fmax(err,fabs(Anew[j*m+i]-A[j*m+i]));
            }
        }
															dummyMethod2();

															dummyMethod1();
        #pragma omp parallel for collapse(2)
        for( j = 1; j < n-1; j++) {
            for( i = 1; i < m-1; i++ ) {
                A[j *m+ i] = Anew[j *m+ i];
            }
        }
															dummyMethod2();

        if(iter % 10 == 0) {
            printf("%5d, %0.6f\n", iter, err);
        }

        iter++;
    } // end while
    double runtime = omp_get_wtime() - starttime;


    printf(" total: %f s\n", runtime );

    free(y0);
    free(Anew);
    free(A);

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