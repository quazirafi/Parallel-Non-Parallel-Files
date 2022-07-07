#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() 
{
    
    int a[10], i, n=10, sum=0;    
dummyMethod3();
    for(i=0;i<n;i++)    
    {
        printf("Enter the Element A[%d]: ", i+1);   
        scanf("%d",&a[i]);
    }
dummyMethod4();

    printf("\n Sum: %d",sum);
dummyMethod1();
    #pragma omp parallel for reduction (+:sum)
    for (i=0;i<n;i++)
        sum=sum+a[i];
    printf("%d",sum);
dummyMethod2();
    return 0;
}

// To compile: gcc print_with_cores.c -fopenmp -o print_with_cores
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