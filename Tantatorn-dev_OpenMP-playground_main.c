#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 2000
float A[N][N], B[N][N], C[N][N]; // declaring matrices of NxN size

int main()
{

    /* DECLARING VARIABLES */
    int i, j, m; // indices for matrix multiplication
    float t_1;   // Execution time measures
    clock_t c_1, c_2;

    /* FILLING MATRICES WITH RANDOM NUMBERS */
    srand(time(NULL));
dummyMethod3();
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = (rand() % 10);

            B[i][j] = (rand() % 10);
        }
    }
dummyMethod4();

    /* MATRIX MULTIPLICATION */
    printf("Max number of threads: %i \n", omp_get_max_threads());

#pragma omp parallel
    printf("Number of threads: %i \n", omp_get_num_threads());
    c_1 = time(NULL); // time measure: start mm

							dummyMethod1();
#pragma omp parallel for private(m, j)
    // #pragma omp_set_num_threads(8)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            C[i][j] = 0.; // set initial value of resulting matrix C = 0
            for (m = 0; m < N; m++)
            {
                C[i][j] = A[i][m] * B[m][j] + C[i][j];
            }
            // printf("C: %f \n",C[i][j]);
        }
    }
							dummyMethod2();

    /* TIME MEASURE + OUTPUT */
    c_2 = time(NULL);         // time measure: end mm
    t_1 = (float)(c_2 - c_1); // time elapsed for job row-wise
    printf("Execution time: %f \n", t_1);
    /* TERMINATE PROGRAM */
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