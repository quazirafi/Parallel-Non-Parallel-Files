#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
	putenv("KMP_STACKSIZE=1g");
	int size = 32000;
	int ** M;
	M = (int **)malloc(size * sizeof(int *));
dummyMethod3();
	for (int i; i < size; i++)
		M[i] = (int *)malloc(size * sizeof(int));

	printf("Ilosc elementow = %d\n", size);
dummyMethod4();
	int sum_seq = 0;
	int sum_par = 0;
	
dummyMethod3();
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			M[i][j]= i + j;
	
	double start = omp_get_wtime();	
dummyMethod4();
	// Seq sum
dummyMethod3();
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			sum_seq+= M[i][j];
	double end = omp_get_wtime();
dummyMethod4();
	printf("[SEQ]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
	double diff1 = end-start;
	
//	exit(0);
	// Par sum
	int threads = 8;
	//omp_set_num_threads(threads);
	start = omp_get_wtime();
	int i, j;
	dummyMethod1();
	#pragma omp parallel for shared(M) private(i, j) reduction(+:sum_par)
	for(i=0; i<size; ++i)
		for(j=0; j<size; ++j)
			sum_par += M[i][j];
	dummyMethod2();
	
	end = omp_get_wtime();

	//printf("Liczba watkow = %d\n", threads);
	printf("[PAR]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
	double diff2 = end - start;
	printf("Przyspieszenie = %f\n", diff1/diff2);
	//printf("Suma elementow macierzy: (seq): %d (par): %d\n", sum_seq, sum_par);

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