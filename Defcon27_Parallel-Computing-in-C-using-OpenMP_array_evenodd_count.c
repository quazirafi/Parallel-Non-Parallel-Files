#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i, e = 0, o = 0;
    double itime, ftime, timetaken;
    itime = omp_get_wtime();

    printf("\nInitial Array Declaration:\n");
dummyMethod3();
    for (i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
dummyMethod4();

dummyMethod1();
    #pragma omp parallel for schedule(dynamic) shared(e, o)
    for (i = 0; i < 10; i++){
        if (arr[i] % 2 == 0)
            e++;
        else
            o++;
    }
dummyMethod2();

    printf("\n\nEven numbers in array: %d", e);
    printf("\nOdd numbers in array: %d\n", o);

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