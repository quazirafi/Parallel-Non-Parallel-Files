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
    int i, ssquares = 0, scubes = 0;
    double itime, ftime, timetaken;
    itime = omp_get_wtime();

    printf("\nInitial Array Declaration:\n");
dummyMethod3();
    for (i = 0; i < 9; i++){
        printf("%d ", arr[i]);
    }
dummyMethod4();

dummyMethod1();
    #pragma omp parallel for schedule(dynamic) shared(ssquares, scubes)
    for (i = 0; i < 9; i++){
        ssquares += pow(arr[i], 2);
        scubes += pow(arr[i], 3);
    }
dummyMethod2();

    printf("\n\nSum of Squares in array: %d", ssquares);
    printf("\nSum of Cubes in array: %d\n", scubes);

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