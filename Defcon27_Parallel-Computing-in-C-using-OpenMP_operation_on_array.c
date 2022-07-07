#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int i;
    double itime, ftime, timetaken;
    itime = omp_get_wtime();

    printf("\nInitial Array Declaration:\n");
dummyMethod3();
    for (i = 0; i < 5; i++){
        printf("%d ", arr[i]);
    }
dummyMethod4();

dummyMethod1();
    #pragma omp parallel for ordered schedule(dynamic)
    for (i = 0; i < 5; i++){
        arr[i] = arr[i] * 5;
        arr[i] = arr[i] + 3;
    }
dummyMethod2();

    printf("\n\nArray after construct\n");
dummyMethod3();
    for (i = 0; i < 5; i++){
        printf("%d ", arr[i]);
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