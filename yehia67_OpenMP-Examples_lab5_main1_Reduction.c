//gcc -fopenmp lab5_main1_Reduction.c
//./a.out 
#include "omp.h"
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

 
int main()
{
    int arr[10] = {1, 3, 5, 6, 7, 9, 3, 4, 2, 8};
    int size = 10;
    
    omp_set_num_threads(4);
    int sum = redundant;

dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}
dummyMethod2();

	redundant = sum - 45;
    printf("the redundant no =  %d \n",redundant);

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