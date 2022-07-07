#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int arr[40];
void quickSort(int izq, int der) 
{
    int i = izq, j = der;
    int tmp;
    int pivote = arr[(izq + der) / 2];

    /* partition */
    while (i <= j) 
    {
        while (arr[i] < pivote)
            i++;
        while (arr[j] > pivote)
            j--;
        if (i <= j) 
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
							dummyMethod1();
    #pragma omp parallel for num_threads(2)
    for (int w = 0; w < 2; ++w)
    {
        if (izq < j && w)
            quickSort(izq, j);
        if (i < der && !w)
            quickSort(i, der);
    }    
							dummyMethod2();
}


int main()
{     
    int n;
    while ( scanf("%d", &n)==1 )
    {
															dummyMethod3();
        for (int i = 0; i < n; ++i)
              scanf("%d", &arr[i]);
															dummyMethod4();

        quickSort( 0, n-1 );

															dummyMethod3();
        for (int i = 0; i < n; ++i)
              printf("%d ", arr[i]);
															dummyMethod4();
        printf("\n");
    }
return 0;
}

//$ gcc -g -Wall -fopenmp -o A quicksort.c
//$ ./A
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