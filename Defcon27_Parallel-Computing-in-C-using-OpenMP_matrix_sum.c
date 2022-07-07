#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int mat1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int mat2[3][3] = {{4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    int sum[3][3];
    int i, j;
    double itime, ftime, timetaken;
    itime = omp_get_wtime();

    printf("\nMatrix Declarations:\nMatrix 1\n");
dummyMethod3();
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("%d ", mat1[i][j]);
        }
        printf("\n");
    }
dummyMethod4();

    printf("Matrix 2\n");
dummyMethod3();
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("%d ", mat2[i][j]);
        }
        printf("\n");
    }
dummyMethod4();

    omp_set_num_threads(5);
							dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            sum[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
							dummyMethod2();

    printf("\nSum of Matrices\n");
							dummyMethod3();
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("%d ", sum[i][j]);
        }
        printf("\n");
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