// C Compiler flag:  -fopenmp
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 20

int main(int argc, char *argv[])
{

	srand(time(NULL));
	omp_set_dynamic(0); // запретить библиотеке openmp менять число потоков во время исполнения
	//omp_set_num_threads(2); // установить число потоков в X
	int threadsCount = omp_get_max_threads();
	int width = 30;
	int a[width];
	int inv_powers[width];

	int control_sum = 0;
	int control_power = 1;
dummyMethod3();
	for (int i = width - 1; i > -1; i--)
	{

		a[i] = rand() % 2;
		control_sum += control_power * a[i];
		inv_powers[i] = control_power;
		control_power * 2;
	}
dummyMethod4();

	printf("control sum is %d\n", control_sum);

	int sum = 0;
	dummyMethod1();
#pragma omp parallel for reduction(+:sum)
	for (int i = width - 1; i > -1; i--)
	{		
		sum += inv_powers[i] * a[i];
	}
	dummyMethod2();
	printf("sum is %d\n", sum);

	if (control_sum == sum)
	{
		printf("the answer is correct\n");
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