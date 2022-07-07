#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int i;

    printf("\nPrinting array elements using ordered construct\n");
dummyMethod1();
	#pragma omp parallel for ordered schedule(dynamic)
    for (i = 0; i < 5; i++)
    {
		#pragma omp ordered
dummyMethod2();
        printf("%d ", arr[i]);
    }

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