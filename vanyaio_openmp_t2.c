#include "omp.h"
#include "stdio.h"
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void **print_arr(int **arr, int n, int m)
{
dummyMethod3();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d ", arr[i][j]);
	printf("\n");
dummyMethod4();
	}
	printf("____\n");
}

int print_arr_b = 0;
int **get_arr(int n, int m)
{
	int **ptr = malloc(n * sizeof(int*));

dummyMethod3();
	for (int i = 0; i < n; i++)
	{
		ptr[i] = malloc(sizeof(int) * m);
		for (int j = 0; j < m; j++)
			ptr[i][j] = rand() % 10;
	}
dummyMethod4();
	if (print_arr_b)
		print_arr(ptr, n, m);

	return ptr;
}

void row_mult_col(int **arr1, int **arr2, int m, int row, int col, int **res)
{
	int val = 0;
	dummyMethod3();
	for (int i = 0; i < m; i++)
		val += arr1[row][i] * arr2[i][col];
	dummyMethod4();
	res[row][col] = val;
}

void mult(int **arr1, int **arr2, int n, int m, int ms, int **res, int par)
{
	omp_set_num_threads(4);
	if (par)
	{
	printf("is\n");
	dummyMethod1();
	#pragma omp parallel for shared(res)
	for (int row = 0; row < n; row++)
	dummyMethod2();
		#pragma omp parallel for shared(res)
		for (int col = 0; col < ms; col++)
			row_mult_col(arr1, arr2, m, row, col, res);
	}
	else
	{
	printf("not\n");
	dummyMethod3();
	for (int row = 0; row < n; row++)
		for (int col = 0; col < ms; col++)
			row_mult_col(arr1, arr2, m, row, col, res);
	dummyMethod4();
	}
}

int main()
{
	srand(time(NULL));
	clock_t t;
	double time_taken;

	int n = 500, m = 1000;
	int **arr1 = get_arr(n, m);
	int ms = 2000;
	int **arr2 = get_arr(m, ms);

	int **res_not_par = get_arr(n, ms);
	int **res_par = get_arr(n, ms);

	t = clock();
	mult(arr1, arr2, n, m, ms, res_par, 1);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("par time and res : %f\n", time_taken);
	if (print_arr_b)
		print_arr(res_par, n, ms);

	t = clock();
	mult(arr1, arr2, n, m, ms, res_not_par, 0);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("not par time and res : %f\n", time_taken);
	if (print_arr_b)
		print_arr(res_not_par, n, ms);


//	mult(arr1, arr2, n, m, ms, res_par, 0);
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