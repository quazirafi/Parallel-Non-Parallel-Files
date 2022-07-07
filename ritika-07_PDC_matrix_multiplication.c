#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 5
int A[N][N];
int B[N][N];
int C[N][N];

int main() 
{
    int i,j,k;
    double time1, time2, total;
	time1 = omp_get_wtime ( );
    omp_set_num_threads(omp_get_num_procs());
dummyMethod3();
    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
	{
            A[i][j] = 2;
            B[i][j] = 3;
	}
dummyMethod4();
dummyMethod1();
    #pragma omp parallel for private(i,j,k) shared(A,B,C)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
dummyMethod2();

    printf("\nDone by, Ritika Kayal 18BCE2518\n\n");
    printf("\nMatrix A:\n", total);
							dummyMethod3();
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",A[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
    printf("\nMatrix B:\n", total);
							dummyMethod3();
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",B[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
	printf("\nAnswer\n", total);
							dummyMethod3();
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",C[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
    time2 = omp_get_wtime ( );
    total = time2 - time1;
    printf("\nTotal time = %f seconds\n\n", total);
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