/*
    Parallel implementation of prefix sum using OpenMP (Hillis Steele Scan)
    compile using: 
        gcc -fopenmp  parallel_prefixsum.c -lm
*/
#include <stdio.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    // test values

    // int arr[] = { 1, 2, 3, 4, 5,6,7,8};
    // int n = 8;
    
    int i, j, k;
    int n;
    int t[n];

    //input of the array
    printf("Enter the size of the array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elements of the array: ");
dummyMethod3();
    for(i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
dummyMethod4();

    // Prefix sum using Hillis and Steele Algorithm
    for(i = 0; i < log2(n); i++)
    {
        int gap = pow(2,i);

															dummyMethod1();
        #pragma omp parallel for private(j) 
        for(j = 0; j < n; j++)
        {
            if(j < gap)
            {
                t[j] = arr[j];
            }
            else
            {
                int index = j - gap;
                t[j] = arr[index] + arr[j];
            }
            
        }
															dummyMethod2();

        printf("Array after pass %d: ",i);
        // swap t and arr
        for(k = 0; k < n; k++)
        {
            printf("%d, ",t[k]);
            int temp = arr[i];
            arr[k] = t[k];
            t[k] = temp;
        }
        printf("\n");
    }


    prinf("\nPrefix sum array: \n");
    // Print array
    for(i = 0; i < n; i++)
        printf("%d, ", arr[i]);

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