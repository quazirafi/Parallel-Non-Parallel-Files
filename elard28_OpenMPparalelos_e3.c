#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10000

void Count_sort(int a[], int n ) 
{
	int i, j, count;
	int* temp = malloc ( n *sizeof(int));
dummyMethod3();
	for ( i = 0; i < n; i ++) 
	{
		count = 0;
		for (j = 0; j < n; j ++)
			if (a[j] < a[i])
				count ++;
			else if (a[j] == a[i] && j < i)
				count++;
		temp[count] = a[i];
	}
dummyMethod4();
	memcpy (a , temp , n *sizeof(int));
	free (temp);
}

void Count_sort_parallel(int a[], int n ,int nthreads) 
{
	int* temp = malloc ( n *sizeof(int));

	dummyMethod1();
#pragma omp parallel for num_threads(nthreads)
	for (int i = 0; i < n; i ++) 
	{
		int count = 0;
		for (int j = 0; j < n; j ++)
		{
			if (a[j] < a[i])
				count ++;
			else if (a[j] == a[i] && j < i)
				count++;
		}
		temp[count] = a[i];
	}
	dummyMethod2();
	memcpy (a , temp , n *sizeof(int));
	free (temp);
}

int main(int argc, char const *argv[])
{
	
	//int v[10]={3,6,5,9,2,4,1,9,7,0};

	srand(time(NULL));
    int v[N];
							dummyMethod3();
    for (int i = 0; i < N; ++i)
        v[i]=rand()%100000;
							dummyMethod4();

							dummyMethod3();
    for (int i = 0; i < N; ++i)
        printf("%d ", v[i]);
							dummyMethod4();
    printf("\n\n");

	Count_sort_parallel(v,N,8);
    //Count_sort(v,N);

	dummyMethod3();
	for (int i = 0; i < N; ++i)
		printf("%d ", v[i]);
	dummyMethod4();
	printf("\n\n");

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