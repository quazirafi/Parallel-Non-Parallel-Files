/**  This Program uses Parallel construct clause variables like Private, firstprivate, shared, default, copyin and Reduction.
 *   Sai Suraj
 *   07/09/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int a = 12345;
#pragma omp threadprivate(a)
 
int main(int argc, char* argv[])
{
    omp_set_num_threads(4);//set number of threads to 4
    int Number = 246810;
    printf("\n\nPrivate Clause: \n\n\tValue Before Parallel Private Region : %d.\n", Number);
 
    #pragma omp parallel private(Number)
    {
        printf("Thread %d : \"val\" = %d.\n", omp_get_thread_num(), Number);
        Number = omp_get_thread_num();
    }
    // Value after the parallel region; unchanged.
    printf("\tValue After Parallel Private Region : %d.\n", Number);

    printf("\n\nFirstPrivate Clause: \n\n\tValue Before Parallel FirstPrivate Region : %d.\n", Number);
    #pragma omp parallel firstprivate(Number)
    {
        printf("Thread %d : \"val\" = %d.\n", omp_get_thread_num(), Number);
        Number = omp_get_thread_num();
    }
    // Value after the parallel region; unchanged.
    printf("\tValue After Parallel FirstPrivate Region %d.\n", Number);

    Number = 555; 
    printf("\n\nShared Clause: \n\n\tValue Before Parallel Shared Region : %d.\n", Number);
 
    #pragma omp parallel shared(Number)
    {
        printf("Thread %d : Value is %d.\n",omp_get_thread_num(), Number);
        #pragma omp master
        {
            printf("Thread %d : Changed value to 978.\n",omp_get_thread_num());
            Number = 978;
        }
        printf("Thread %d : Value is %d.\n",omp_get_thread_num(), Number);
    }
    printf("After Parallel Region : Value is %d.\n", Number);

    int val = 0;
    printf("\n\nDefault Clause:\n");
    #pragma omp parallel default(shared)
    {
        if(omp_get_thread_num() <= 1)
        {
            printf("Thread %d sets the value of \"val\" to 123.\n",omp_get_thread_num());
            val = 12345;
        }
        printf("Thread %d reads the value of \"val\": %d.\n", omp_get_thread_num(),val);
    }

    printf("\n\nCopyin Clause: \n\tValue Before Parallel Copyin Region : %d.\n", a);
    #pragma omp parallel copyin(a)
    {
        #pragma omp master
        {
            printf("First parallel region: Master thread value to 67890.\n");
            a = 67890;
        }
        printf("First parallel region: Thread %d: Value = %d.\n", omp_get_thread_num(), a);
    }
    #pragma omp parallel copyin(a)
    {
        printf("Second parallel region: Thread %d: Value = %d.\n", omp_get_thread_num(), a);
    }

// Use 2 threads when creating OpenMP parallel regions
    omp_set_num_threads(4);
    int Value = 10;
    int Sum = 0;
							dummyMethod1();
    #pragma omp parallel for default(none) firstprivate(Value) reduction(+: Sum)
    for (int i = 0; i < Value; i++) 
    {
    
         Sum += (i+1);
    }
							dummyMethod2();
    printf("\nSum of %d = %d\n\n", Value, Sum);
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