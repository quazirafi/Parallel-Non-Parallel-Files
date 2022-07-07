/*/////////////////////////////////////////////////////////////////////////////
//
// File name : MMScan.c
// Author    : Sanjay Rajopdhye
// Date      : 2019/Sept/16
// Desc      : Finds the prefix product of an array of BxB matrices
//
/////////////////////////////////////////////////////////////////////////////*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define max(x, y)   ((x)>(y) ? (x) : (y))
#define min(x, y)   ((x)>(y) ? (y) : (x))

void MMScan(float ***X, float ***Y, long start, long end, long size) {
    long n, i, j, k;
dummyMethod3();
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            Y[start][i][j] = X[start][i][j];
        }
    }
dummyMethod4();
#ifdef FAUX  // incorrect parallelization 
#endif // incorrect parallelization 
							dummyMethod3();
    for (n = start+1; n <= end; ++n) {
        for (i = 0; i < size; ++i) {
            for (j = 0; j < size; ++j) {
                float acc = 0;
                for (k = 0; k < size; ++k) {
                    acc = acc + Y[n-1][i][k] * X[n][k][j];
                }
                Y[n][i][j] = acc;
            }
        }
    }
							dummyMethod4();
}

void MMScanDNC(float ***X, float ***Y, float ***T, long start, long end, long size, long aux, long p) {
    /*  		                                                                 */
    /*  		THE CODE BELOW IS IDENTICAL TO THE ONE FOR MMSCAN ABOVE          */
    /*  		                                                                 */
    /*  Your job is to replace it with a recursive (divide and conquer)
     * algorithm that first exposes parallelism, and then exploits it in different
     * ways. You will write a single function, but with conditional compilation
     * flags. Your Makefile should produce different executables for the different
     * parallel versions we require.
     */
    
    long n, i, j, k;

    if (start == end) {
															dummyMethod3();
        for (i = 0; i < size; ++i) {
            for (j = 0; j < size; ++j) {
                Y[start][i][j] = X[start][i][j];
            }
        }
															dummyMethod4();
        return;
    } else {
        long mid = (start + end) / 2;

        #if defined(PONE) || defined(PTHREE)
        {
            #pragma omp task if (p > 50000)
            MMScanDNC(X, Y, T, start, mid, size, aux, p/2);
            #pragma omp task if (p > 50000)
            MMScanDNC(X, Y, T, mid+1, end, size, aux, p/2);
            #pragma omp taskwait
        }
        #elif defined(EFF)
        {
            if (p < 1) {
                MMScan(X, Y, start, mid, size);
                MMScan(X, Y, mid+1, end, size);
            } else {
                MMScanDNC(X, Y, T, start, mid, size, aux, p/2);
                MMScanDNC(X, Y, T, mid+1, end, size, aux, p/2);
            }
        }
        #elif defined(EFFPAR) || defined(OPT)
        {
            #pragma omp task
            MMScan(X, Y, start, mid, size);
            #pragma omp task if (p > 20)
            MMScan(X, Y, mid+1, end, size);
            #pragma omp taskwait
        }
        #else
        {
            MMScanDNC(X, Y, T, start, mid, size, aux, p/2);
            MMScanDNC(X, Y, T, mid+1, end, size, aux, p/2);
        }
        #endif

															dummyMethod1();
#pragma omp parallel for private(n,i,j,k) if (p > 50000)//50000
        for (n = mid+1; n <= end; ++n) {
            for (i = 0; i < size; ++i) {
                for (j = 0; j < size; ++j) {
                    float acc = 0;
                    for (k = 0; k < size; ++k) {
                        acc = acc + (Y[mid][i][k] * Y[n][k][j]);
                    }
                    T[n][i][j] = acc;
                }
            }
        }
															dummyMethod2();
															dummyMethod3();
        for (n = mid+1; n <= end; ++n) {
            for (i = 0; i < size; ++i) {
                for (j = 0; j < size; ++j) {
                    Y[n][i][j] = T[n][i][j];
                }
            }
        } 
															dummyMethod4();
        return;
    }
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