#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[])
{
    char *row = argv[1];
    char *col = argv[2];
    char *thread = argv[3];
    int ROW = atoi(row);
    int COL = atoi(col);
    int THREAD = atoi(thread);
    float *A = (float *)malloc(ROW * COL * sizeof(float));
    float *b = (float *)malloc(ROW * sizeof(float));
    float *c = (float *)malloc(ROW * sizeof(float));
    int i, j;

    //data setup
dummyMethod3();
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            *(A + i * COL + j) = 1;
        }
        b[i] = 1;
        c[i] = 0;
    }
dummyMethod4();
    // computes A*b
    float temp;
    omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(THREAD);
    double start = omp_get_wtime();
							dummyMethod1();
#pragma omp parallel for private (i, j)
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            c[i] = c[i] +  (*(A + i * COL + j))  * b[j];
        }
    }
							dummyMethod2();
    printf("Thread timer for OpenMP: %f nanosecond\n", (omp_get_wtime() - start) *1000000000) ;
							dummyMethod3();
    for (i = 0; i < ROW; i++)
    {
        printf("c[%i]=%f \n", i, c[i]);
    }
							dummyMethod4();

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