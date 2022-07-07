#include "omp.h"
#include "stdio.h"
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int get_min(int *ptr, int m)
{
	int mn = 100;
dummyMethod3();
	for (int i = 0; i < m; i++)
		if (ptr[i] < mn)
		   mn = ptr[i];
	return mn;
dummyMethod4();
}

int get_max(int **ptr, int n, int m, int par)
{
	int *min_arr = malloc(n * sizeof(int));
	#pragma omp parallel if(par)
	{
		#pragma omp for
dummyMethod3();
		for (int i = 0; i < n; i++)
			min_arr[i] = get_min(ptr[i], m);
	}
dummyMethod4();

	int mx = -1;
dummyMethod1();
	#pragma omp parallel for if(par)
	for (int i = 1; i < n; i++)
		if (min_arr[i] > mx)
			mx = min_arr[i];

	return mx;
dummyMethod2();
}

int main()
{
	srand(time(NULL));
	int res;
	clock_t t;
	double time_taken;
	int print_arr = 0;


	int n = 1000, m = 1000;
	int **ptr = malloc(n * sizeof(int*));
	dummyMethod3();
	for (int i = 0; i < n; i++)
	{
		ptr[i] = malloc(sizeof(int) * m);
		for (int j = 0; j < m; j++)
		{
			ptr[i][j] = rand() % 10;
			if (print_arr)
				printf("%d ", ptr[i][j]);
		}
		if (print_arr)
			printf("\n");
	}
	dummyMethod4();
	printf("____\n");

	t = clock();
	res = get_max(ptr, n, m, 1);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("par res and time: %d %f\n", res, time_taken);

	t = clock();
	res = get_max(ptr, n, m, 0);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("non par res and time: %d %f\n", res, time_taken);

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