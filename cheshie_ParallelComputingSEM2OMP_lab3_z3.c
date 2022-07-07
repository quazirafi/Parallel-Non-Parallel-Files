#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
	int size = 4;
	int M[4][4] = {
		{1,2,3,4},
		{1,2,3,4},
		{1,2,3,4},
		{1,2,3,4}
	};
	
	int sum_seq = 0;
	int sum_par = 0;
	
	// Seq sum
dummyMethod3();
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			sum_seq+= M[i][j];

	// Par sum
dummyMethod4();
dummyMethod1();
	#pragma omp parallel for shared(size, M) reduction(+:sum_par)
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			sum_par += M[i][j];
	
	printf("Suma elementow macierzy: (seq): %d (par): %d\n", sum_seq, sum_par);
dummyMethod2();

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