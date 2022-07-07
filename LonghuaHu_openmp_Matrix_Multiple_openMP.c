#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 2000
#define FactorIntToDouble 1.1; 
#define NUM_THREADS 4

double firstMatrix [N] [N] = {0.0};
double secondMatrix [N] [N] = {0.0};
double matrixMultiResult [N] [N] = {0.0};


void matrixMulti()
{
dummyMethod1();
#pragma omp parallel for default(none) schedule(static, 4) num_threads(NUM_THREADS)
    for(int row = 0 ; row < N ; row++){
        for(int col = 0; col < N ; col++){
            double resultValue = 0;
            for(int transNumber = 0 ; transNumber < N ; transNumber++) {
                resultValue += firstMatrix [row] [transNumber] * secondMatrix [transNumber] [col] ;
            }

            matrixMultiResult [row] [col] = resultValue;
        }
    }
dummyMethod2();
}


void matrixInit()
{
							dummyMethod3();
    for(int row = 0 ; row < N ; row++ ) {
        for(int col = 0 ; col < N ;col++){
            srand(row+col);
            firstMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
            secondMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
        }
    }
							dummyMethod4();
}



int main()
{
    //omp_set_num_threads(NUM_THREADS);
    matrixInit();
    double time_spent = 0.0;
    clock_t t1 = clock();
    
    matrixMulti();
    clock_t t2 = clock();
    time_spent += (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("Time elpased is %f seconds\n", time_spent);

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