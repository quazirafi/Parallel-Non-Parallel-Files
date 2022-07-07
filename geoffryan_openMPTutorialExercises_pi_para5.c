#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 100000000;

int main()
{
    double pi;
    double t1, t2;
    
    t1 = omp_get_wtime();
    double step = 1.0/((double) num_steps);
    double sum;
    long i;

dummyMethod1();
    #pragma omp parallel for schedule(auto) reduction(+:sum)
    for(i=0; i<num_steps; i++)
    {
        double x = (i+0.5)*step;
        sum += 4.0/(1.0+x*x);
    }
dummyMethod2();

    pi = step*sum;

    t2 = omp_get_wtime();

    printf("pi = %1.12f in %1.12f seconds\n", pi, t2-t1);
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