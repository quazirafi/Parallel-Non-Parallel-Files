#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int absum_vector(int csum, int el){
    int sum;
    sum = el >= 0 ? csum + el : csum - el;
    return sum;
}

#pragma omp declare reduction(absumv: int:\ 
        omp_out=absum_vector(omp_out, omp_in))\
        initializer(omp_priv=0)

int main(int argc, char *argv[])
{
    int size = 2000000;
    int vec[size];
dummyMethod3();
    for(int i=0; i < size; i++)
        vec[i] = (rand() % 100) - (rand()  % 50);
    int sum;
dummyMethod4();

    double start = omp_get_wtime();
    omp_set_num_threads(atoi(argv[1]));

dummyMethod1();
    #pragma omp parallel for reduction(absumv: sum)
    for (int i=0; i < size; i++){
        sum = absum_vector(sum, vec[i]);
    }
dummyMethod2();

    double end = omp_get_wtime();
    printf("start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);

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