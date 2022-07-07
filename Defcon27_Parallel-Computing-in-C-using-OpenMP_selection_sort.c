#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{

	int arr[] = {4, 16, 1, 2, 13, 17, 20, 5, 2, 13, 8, 6, 11, 18, 13, 14, 12, 18, 19, 5};
	int n = sizeof(arr) / sizeof(arr[0]);
	double itime, ftime, timegap;
	int x;
	printf("Unsorted order\n");
dummyMethod3();
	for (x = 0; x < n; x++)
	{
		printf("%d ", arr[x]);
	}
dummyMethod4();
	itime = omp_get_wtime();
	
	// Selection Sort
	int i, j, t, min_idx;
	for (i = 0; i < n; i++)
	{
        min_idx = i;
dummyMethod1();
		#pragma omp parallel for schedule(dynamic) private(j)
		for (j = i; j < n; j++)
		{
			if (arr[j] < arr[min_idx]){
				min_idx=j;
			}
		}
dummyMethod2();
		t = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = t;
	}

	printf("\n\nSorted Order\n");
	for (i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}

	ftime = omp_get_wtime();
	timegap = ftime - itime;
	printf("\n\nTime taken is is %f", timegap);
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