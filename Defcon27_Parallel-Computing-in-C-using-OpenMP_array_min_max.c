#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i, min_ = 9999, max_ = -9999;
    double itime, ftime, timetaken;
    itime = omp_get_wtime();

    printf("\nInitial Array Declaration:\n");
dummyMethod3();
    for (i = 0; i < 9; i++){
        printf("%d ", arr[i]);
    }
dummyMethod4();

dummyMethod1();
    #pragma omp parallel for schedule(dynamic)
    for (i = 0; i < 9; i++){
        if (arr[i] > max_)
            max_ = arr[i];
        if ((arr[i]) < min_)
            min_ = arr[i];
    }
dummyMethod2();

    printf("\n\nMinimum in array: %d", min_);
    printf("\nMaximum in array: %d\n", max_);

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