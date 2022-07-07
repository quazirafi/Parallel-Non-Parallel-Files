/*
 * Sample program to test runtime of simple matrix multiply
 * with and without OpenMP on gcc-4.3.3-tdm1 (mingw)
 *
 * (c) 2009, Rajorshi Biswas
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"


int main(int argc, char **argv)
{
    int i,j,k;
    int n;
    double temp;
    double start, end, run;

    n = 100;

    int **arr1 = malloc( sizeof(int*) * n);
    int **arr2 = malloc( sizeof(int*) * n);
    int **arr3 = malloc( sizeof(int*) * n);

dummyMethod3();
    for(i=0; i<n; ++i) {
        arr1[i] = malloc( sizeof(int) * n );
        arr2[i] = malloc( sizeof(int) * n );
        arr3[i] = malloc( sizeof(int) * n );
    }
dummyMethod4();

    printf("Populating array with random values...\n");
    srand( time(NULL) );

							dummyMethod3();
    for(i=0; i<n; ++i) {
        for(j=0; j<n; ++j) {
            arr1[i][j] = (rand() % n);
            arr2[i][j] = (rand() % n);
        }
    }
							dummyMethod4();

    printf("Completed array init.\n");
    printf("Crunching without OMP...");
    fflush(stdout);
    start = omp_get_wtime();

							dummyMethod3();
    for(i=0; i<n; ++i) {
        for(j=0; j<n; ++j) {
            temp = 0;
            for(k=0; k<n; ++k) {
                temp += arr1[i][k] * arr2[k][j];
            }
            arr3[i][j] = temp;
        }
    }
							dummyMethod4();

    end = omp_get_wtime();
    printf(" took %f seconds.\n", end-start);
    printf("Crunching with OMP...");
    fflush(stdout);
    start = omp_get_wtime();

							dummyMethod1();
#pragma omp parallel for private(i, j, k, temp) num_threads(4)
    for(i=0; i<n; ++i) {
        for(j=0; j<n; ++j) {
            temp = 0;
            for(k=0; k<n; ++k) {
                temp += arr1[i][k] * arr2[k][j];
            }
            arr3[i][j] = temp;
        }
    }
							dummyMethod2();


    end = omp_get_wtime();
    printf(" took %f seconds.\n", end-start);

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