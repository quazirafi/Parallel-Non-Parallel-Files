#include <stdio.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{

    double x, dx, y, r1, r2, area = 0.0;
    int i;
    double itime, ftime, timetaken;
    itime = omp_get_wtime();
    int iters = 10000000;
    dx = 1.0 / (double)iters;
    x = dx;

dummyMethod1();
    #pragma omp parallel for schedule(dynamic) reduction(+: area) private(x, y, i, dx)
    for (i = 1; i < iters; i++)
    {
        dx = 1.0 / (double)iters;
        x = (double)i * dx;
        y = sqrt((double)1.0 - (pow(x, 2)));
        area += dx * y;
    }
dummyMethod2();
    printf("\nPI value calculated is %f", area * 4.0);

    ftime = omp_get_wtime();
    timetaken = ftime - itime;
    printf("\n\nTime Taken = %f", timetaken);
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