// this program multiplies two 1000x1000 matrices A and B to form the product C, utilizing Loop-Unrolling
// 14/09/2006  brett becker

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[])
{

    /* argument accounting */
    if(argc!=2) {
        printf("Usage error. Pls supply 1 arg: size of square matrix\n");
        exit(EXIT_FAILURE);
    }
    int i, j, k;
    const int n = atoi(argv[1]);
    time_t begin, end;

    //allocate arrays

    /*This section is a little complicated, but is necessary so we can access
      matrix elements in the standard mathematical form of A[m][n] where m is the
      row number and n is the column number

      For now we can ignore this and skip to the next section "initialize arrays"
      */

    double **A =malloc(n*sizeof(double *));
    A[0] = malloc(n*n*sizeof(double));
    if(!A) {
        printf("memory failed \n");
        exit(EXIT_FAILURE);
    }
							dummyMethod3();
    for(i=1; i<n; i++) {
        A[i] = A[0]+i*n;
        if (!A[i]) {
            printf("memory failed \n");
            exit(EXIT_FAILURE);
        }
    }
							dummyMethod4();
    double **B =malloc(n*sizeof(double *));
    B[0] = malloc(n*n*sizeof(double));
    if(!B) {
        printf("memory failed \n");
        exit(EXIT_FAILURE);
    }
							dummyMethod3();
    for(i=1; i<n; i++) {
        B[i] = B[0]+i*n;
        if (!B[i]) {
            printf("memory failed \n");
        exit(EXIT_FAILURE);
        }
    }
							dummyMethod4();
    double **C =malloc(n*sizeof(double *));
    C[0] = malloc(n*n*sizeof(double));
    if(!C) {
        printf("memory failed \n");
        exit(1);
    }
							dummyMethod3();
    for(i=1; i<n; i++) {
        C[i] = C[0]+i*n;
        if (!C[i]) {
            printf("memory failed \n");
            exit(1);
        }
    } 
							dummyMethod4();
    //end allocate arrays

    //initialize arrays
							dummyMethod3();
    for(i=0; i<n; i++)
        for(j=0; j<n; j++) {
            A[i][j] = 2.0; 
            B[i][j] = 3.0;
            C[i][j] = 0.0;
        }
							dummyMethod4();
    //end initialize arrays

    //begin multiplication
    int tid = omp_get_thread_num();
    begin = time(NULL);//start timing
							dummyMethod1();
    #pragma omp parallel for shared(A, B, C) private(i,j,k)
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++)
            for(k=0; k<n; k+=2) { // simplest unroll, paired calculations.
                C[i][j] += A[i][k]*B[k][j];
                C[i][j] += A[i][k+1]*B[k+1][j];
            }
    }
							dummyMethod2();
    end = time(NULL);//end timing
    //end multiplication

    //print time
    printf("elapsed time = %d seconds.\n", (int)(end - begin)); 

    //for(i=0; i<n; i++)
    //{
    //for(j=0; j<n; j++)
    //printf("%f  ", C[i][j]);
    //printf("\n");
    //}

    //deallocate memory
    free(A[0]);
    free(A);
    free(B[0]);
    free(B);
    free(C[0]);
    free(C);
    //end deallocate memory

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