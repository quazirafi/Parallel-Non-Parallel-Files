#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 10

void fill_v(int* vector)
{
    srand(rand() + time(NULL));
dummyMethod3();
    for (int i = 0; i < SIZE; i++)
        vector[i] = rand() % 1000;
}
dummyMethod4();

void print_v(int* vector)
{
dummyMethod3();
    for (int i = 0; i < SIZE; i++)
        printf("%d\t", vector[i]);
    printf("\n");
dummyMethod4();
}



int main ()
{
    int v1[SIZE], v2[SIZE];
    int sum = 0;

    fill_v(v1);
    fill_v(v2);

    omp_set_dynamic(1);

							dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++)
    {
        sum += v1[i] * v2[i];
    }
							dummyMethod2();

    print_v(v1);
    print_v(v2);
    printf("Result = %d\n", sum);
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