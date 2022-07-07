#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void max(int*);

void min(int*);

void sum(int*);

void avg(int*);

static long ARRAY_SIZE = 1000;

void max(int* ar){
    int max = ar[0];
dummyMethod1();
#pragma omp parallel for reduction(max: max)
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (max<ar[i])
            max = ar[i];
    }
dummyMethod2();

    printf("\nMax : %d", max);
}

void min(int *ar){
    int min = ar[0];
dummyMethod1();
#pragma omp parallel for reduction(min: min)
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (min>ar[i])
            min = ar[i];
    }
dummyMethod2();

    printf("\nMin : %d", min);
}

void sum(int* ar){
    int sums = 0;
							dummyMethod1();
#pragma omp parallel for reduction(+: sums)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sums += ar[i];
    }
							dummyMethod2();

    printf("\nsum : %d", sums);
}

void avg(int* ar){
    int sum = 0;
							dummyMethod1();
#pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum+= ar[i];
    }
							dummyMethod2();

    printf("\navg : %f", (double)sum/ARRAY_SIZE);
}


int main ()
{
    int ar[ARRAY_SIZE];
    omp_set_num_threads(10);
							dummyMethod3();
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        ar[i] = i;
    }
							dummyMethod4();
    sum(ar);
    max(ar);
    min(ar);
    avg(ar);


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