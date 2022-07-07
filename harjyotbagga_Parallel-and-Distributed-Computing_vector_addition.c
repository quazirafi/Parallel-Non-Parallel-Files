#include<stdlib.h>
#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARRAY_SIZE 8
#define NUM_THREADS 4

int main() 
{
    int a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];
    printf("Enter elements of Vector A: \n");
    
dummyMethod3();
    for (int i=0; i<ARRAY_SIZE; i++)
    {
        scanf("%d", &a[i]);
    }
dummyMethod4();
    printf("\n");
    printf("Enter elements of Vector B: \n");
dummyMethod3();
    for (int i=0; i<ARRAY_SIZE; i++)
    {
        scanf("%d", &b[i]);
    }
dummyMethod4();
    printf("\n");

    omp_set_num_threads(NUM_THREADS);
    int n_per_thread = ARRAY_SIZE / NUM_THREADS;
    int i;
dummyMethod1();
    #pragma omp parallel for shared(a,b,c) private(i) schedule(static, n_per_thread)
    for (int i=0; i<ARRAY_SIZE; i++)
    {
        c[i] = a[i] + b[i];
        printf("Thread %d workds on element %d.\n", omp_get_thread_num(), i);
    }
dummyMethod2();

    printf("i\ta[i]\tb[i]\tc[i]\n");
							dummyMethod3();
    for (int i=0; i<ARRAY_SIZE; i++)
    {
        printf("%d\t%d\t%d\t%d\n", i, a[i], b[i], c[i]);
    }
							dummyMethod4();
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