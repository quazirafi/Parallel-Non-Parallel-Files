#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int partition(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;
    

dummyMethod1();
#pragma omp parallel for
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }   
    }   
dummyMethod2();

dummyMethod3();
    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }   
dummyMethod4();

    a[p + lt_n] = key;

							dummyMethod3();
    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }   
							dummyMethod4();

    return p + lt_n;
    
}


void quicksort(int * a, int p, int r)
{
    int div;

    if(p < r){ 
        div = partition(a, p, r); 
#pragma omp parallel sections
        {   
#pragma omp section
            quicksort(a, p, div - 1); 
#pragma omp section
            quicksort(a, div + 1, r); 

        }
    }
    
}


int main(void)
{   int SIZE =1<<8;
	int a[SIZE];
    double start,end;
	dummyMethod3();
	for(int j=0;j<SIZE;j++)
	{
	    a[j]=rand()%SIZE;
	}
	dummyMethod4();
    int i;
    start=omp_get_wtime();

    quicksort(a, 0, 9);
    end=omp_get_wtime();
    int N = SIZE;

							dummyMethod3();
    for(i = 0;i < N; i++){
        printf("%d\t", a[i]);
    }
							dummyMethod4();
    printf("\n");
    printf("\nquick sort Time Parallel= %f",(end-start));
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