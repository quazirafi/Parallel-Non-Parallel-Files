#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* Main Program */
int main()
{
    double  **InputMatrix, **CheckMatrix;
    int  j, i, N,Noofthreads,total_threads;
    printf("\n\t\t Enter the size of the Matrix\n");
    scanf("%d", &N);
    /* Dynamic Memory Allocation */
    InputMatrix = (double **) malloc(sizeof(double *) * N);
    CheckMatrix = (double **) malloc(sizeof(double *) * N);
    /* Initializing The Matrix Elements */
dummyMethod3();
    for (i = 0; i < N; i++) {
        InputMatrix[i] = (double *) malloc(sizeof(double) * N);
        for (j = 0 ; j < N; j++)
            InputMatrix[i][j] = i + j;
    }
dummyMethod4();
 
    /* CheckMatrix Is Also Same As Input Matrix */
dummyMethod3();
    for (i =0; i < N; i++) {
        CheckMatrix[i] = (double *) malloc(sizeof(double) * N);
        for (j = 0; j < N; j++)
            CheckMatrix[i][j] = InputMatrix[i][j];
    }
dummyMethod4();
    for (j = 1; j < N; j++)
							dummyMethod1();
    #pragma omp parallel for
    for (i = 1; i < N; i++)
                {
                       if ( (omp_get_thread_num()) == 0)
                        {
                            total_threads=omp_get_num_threads();
                         }
            InputMatrix[i][j] = InputMatrix[i][j] + InputMatrix[i][j - 1];
              }/* End of the parallel region */
							dummyMethod2();
    /* For Validity Of Output */
    /* Serial Calculation */
    for (j = 1; j < N; j++)
        for (i = 1; i < N; i++)
            CheckMatrix[i][j] = CheckMatrix[i][j] + CheckMatrix[i][j - 1];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (CheckMatrix[i][j] == InputMatrix[i][j]) {
                continue;
            } else {
                exit(1);
            }
  printf("\n The Output Matrix After Loop Nest Containing a Recurrence \n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%lf\t", InputMatrix[i][j]);
        printf("\n");
    }
    /* Freeing Of Allocated Memory */
    free(InputMatrix);

    free(CheckMatrix);
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