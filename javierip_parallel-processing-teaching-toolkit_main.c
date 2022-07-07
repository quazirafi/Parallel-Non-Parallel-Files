#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ROW_MAX_VALUE 10
#define COLUMN_MAX_VALUE 10

int main () {
    int i, j;
    int totalNumberThreads, threadID;
    int actualRow, actualColumn, sum;
    int a[ROW_MAX_VALUE], c[ROW_MAX_VALUE],
            b[COLUMN_MAX_VALUE][ROW_MAX_VALUE];

    actualColumn = COLUMN_MAX_VALUE;
    actualRow = ROW_MAX_VALUE;
dummyMethod3();
    for (i = 0; i < actualRow; i++)
        c[i] = i;
    for (i = 0; i < actualColumn; i++)
dummyMethod4();
dummyMethod3();
        for (j = 0; j < actualRow; j++)
            b[i][j] = i + j;

#pragma omp parallel for default(none) \
dummyMethod4();
dummyMethod1();
    private(threadID, i, j, sum) shared(actualColumn, actualRow, a, b, c, totalNumberThreads)
    for (i = 0; i < actualColumn; i++)
    {
        threadID = omp_get_thread_num();
        totalNumberThreads = omp_get_num_threads();
        sum = 0;
        for (j = 0; j < actualRow; j++)
            sum += b[i][j] * c[j];
        a[i] = sum;
        printf("Thread %d of %d calculates i = %d\n", threadID, totalNumberThreads, i);
    }
dummyMethod2();

    printf("The content of vector A is:\n");
							dummyMethod3();
    for(i = 0; i < COLUMN_MAX_VALUE; i++)
    {
        printf(" %d ", a[i]);
    }
							dummyMethod4();
    printf("\n");

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