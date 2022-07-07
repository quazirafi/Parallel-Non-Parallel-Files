#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int row_sum[3];
    int i, j;
    double itime, ftime, timetaken;
    itime = omp_get_wtime();

    printf("Matrix Declarations:\nMatrix\n");
dummyMethod3();
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
dummyMethod4();

    omp_set_num_threads(15);
dummyMethod1();
	#pragma omp parallel for shared(row_sum)
    for (i = 0; i < 3; i++){
        row_sum[i] = 0;
        for (j = 0; j < 3; j++){
            row_sum[i] += mat[i][j];
        }
    }
dummyMethod2();

    printf("\nRow sum of Matrix\n");
dummyMethod3();
    for (i = 0; i < 3; i++){
        printf("%d ", row_sum[i]);
    }
dummyMethod4();

    ftime = omp_get_wtime();
    timetaken = ftime - itime;
    printf("\nTime Taken = %f", timetaken);
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