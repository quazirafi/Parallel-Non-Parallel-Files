#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ROWS_A 3//6
#define COLS_A 3//1
#define ROWS_B 3//1
#define COLS_B 3//6


void error (char* errMessage){
    printf("%s", errMessage);
    exit(1);
}

int main()
{

    if (COLS_A != ROWS_B){
        error("Matrix format error\n");
    }
/*
    int matrixA[ROWS_A][COLS_A] = {
        {4},
        {6},
        {4},
        {7},
        {9},
        {-9},
    };
    int matrixB[ROWS_B][COLS_B] = {
        {1, -2, 3, -2, 3, 6},
    };*/

    int matrixA[ROWS_A][COLS_A] = {
        {1, -2, 3},
        {3, 0, 2},
        {3, 6, 1},
    };
    int matrixB[ROWS_B][COLS_B] = {
        {1, -2, 3},
        {3, 0, 2},
        {3, 6, 1},
    };


    int nthreads, tid, a, i, j;

    int res[ROWS_A][COLS_B];
    
    #pragma omp parallel private (tid)
    {
        tid = omp_get_thread_num();
        #pragma omp for private(i,j)
        for( a = 0; a < COLS_B; a++ )
        {
            printf("Hola, soy el thread %d y estoy calculando matrixA * matrixB[x][%d];\n\n",tid,a);
																							dummyMethod1();
            #pragma omp parallel for
            for( i = 0; i < ROWS_A; i++ )
            {
                int sum = 0;
                
                for( j = 0; j < COLS_A; j++ )
                {
                    sum += matrixA[i][j] * matrixB[j][a];
                }
                res[i][a] = sum;
            }
																							dummyMethod2();
        }
        nthreads = omp_get_num_threads();
    }


    printf("Numero total de threads = %d\n", nthreads);


    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }

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