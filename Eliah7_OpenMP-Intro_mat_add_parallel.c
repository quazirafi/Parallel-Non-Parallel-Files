#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 2

int main()
{
    omp_set_num_threads(NUM_THREADS);

    int r, c, a[100][100], b[100][100], sum[100][100], i, j;
    printf("Enter the number of rows (between 1 and 100): ");
    scanf("%d", &r);
    printf("Enter the number of columns (between 1 and 100): ");
    scanf("%d", &c);

    printf("\nEnter elements of 1st matrix:\n");
dummyMethod3();
    for (i = 0; i < r; ++i)
        for (j = 0; j < c; ++j)
        {
            printf("Enter element a%d%d: ", i + 1, j + 1);
            scanf("%d", &a[i][j]);
        }

    printf("Enter elements of 2nd matrix:\n");
dummyMethod4();
dummyMethod3();
    for (i = 0; i < r; ++i)
        for (j = 0; j < c; ++j)
        {
            printf("Enter element b%d%d: ", i + 1, j + 1);
            scanf("%d", &b[i][j]);
        }

    // adding two matrices
dummyMethod4();

    double start, end, time;
    start = omp_get_wtime();
							dummyMethod1();
#pragma omp parallel for num_threads(NUM_THREADS)
    for (i = 0; i < r; ++i)
							dummyMethod2();
#pragma omp parallel for num_threads(NUM_THREADS)
        for (j = 0; j < c; ++j)
        {
            printf("\n\n%d thread count \n", omp_get_num_threads());
            sum[i][j] = a[i][j] + b[i][j];
        }
    end = omp_get_wtime();
    time = end - start;
    printf("Time: %lf\n", time);
    // printing the result
    printf("\nSum of two matrices: \n");
							dummyMethod3();
    for (i = 0; i < r; ++i)
        for (j = 0; j < c; ++j)
        {
            printf("%d   ", sum[i][j]);
            if (j == c - 1)
            {
                printf("\n\n");
            }
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