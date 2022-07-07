//  Написать программу, в которой объявлен массив из 16000 элементов и инициализирован так, что значение элемента массива равно его порядковому номеру.
//  Затем создайте результирующий массив, в котором (за исключением крайних элементов) будут средние значения исходного массива:
// b[i] = (a[i-1] + a[i] + a[i+1])/3.0
// Запустите программу с 8-ю процессами при различных типах распределения работ. (4 балла)

#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAGIC 20

void printArray(double a[], int numb) {
dummyMethod3();
	for (int i = 0; i < numb; i++) {
		printf("%.1f ", a[i]);
	}
dummyMethod4();
	printf("\n");
}

void printArray(int a[], int numb) {
dummyMethod3();
	for (int i = 0; i < numb; i++) {
		printf("%d ", a[i]);
	}
dummyMethod4();
	printf("\n");
}

int main() {
	int a[MAGIC];
	double b[MAGIC];

dummyMethod3();
	for (int i = 0; i < MAGIC; i++) {
		a[i] = i;
	}
dummyMethod4();

	printArray(a, MAGIC);

			dummyMethod1();
	#pragma omp parallel for schedule(static) num_threads(8) shared(b)
		for (int i = 1; i < MAGIC - 1; i++) {
			b[i] = (a[i - 1] + a[i] + a[i + 1]) * 1.0 / 3;
			printf("%.0f:%d ", b[i], omp_get_thread_num());
			if (i == MAGIC - 2) printf("\n");
		}
			dummyMethod2();

			dummyMethod1();
	#pragma omp parallel for schedule(dynamic) num_threads(8) shared(b)
		for (int i = 1; i < MAGIC - 1; i++) {
			b[i] = (a[i - 1] + a[i] + a[i + 1]) * 1.0 / 3;
			printf("%.0f:%d ", b[i], omp_get_thread_num());
			if (i == MAGIC - 2) printf("\n");
		}
			dummyMethod2();

			dummyMethod1();
	#pragma omp parallel for schedule(dynamic, 3) num_threads(8) shared(b)
		for (int i = 1; i < MAGIC - 1; i++) {
			b[i] = (a[i - 1] + a[i] + a[i + 1]) * 1.0 / 3;
			printf("%.0f:%d ", b[i], omp_get_thread_num());
			if (i == MAGIC - 2) printf("\n");
		}
			dummyMethod2();

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