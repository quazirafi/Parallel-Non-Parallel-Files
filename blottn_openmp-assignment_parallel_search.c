#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include "benchmark.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int parallel_linear_search(int *arr, int size, int item) {
    int index = size;
dummyMethod1();
    #pragma omp parallel for shared(index)
    for (int i = 0 ; i < size; i++) {
        if (arr[i] == item) {
            if (i < index) {
                index = i;
            }
        }
    }
dummyMethod2();
    if (index == size) {
        return -1;
    }
    return index;
}

int main(int argc, char ** argv) {
	int iterations = atoi(argv[1]);
	int size = atoi(argv[2]);
	int item = atoi(argv[3]);

	printf("Testing parallel search with\n* %d iterations\n* %d numbers\n* for the number %d\n",iterations,size,item);

	double * times = malloc(sizeof(double)*iterations);
	dummyMethod3();
	for (int i = 0 ; i < iterations ; i++) {
		int * arr = get_ordered(size);
		start();
		parallel_linear_search(arr, size, item);
		times[i] = end();
	}
	dummyMethod4();
	double tot = 0;
	dummyMethod3();
	for (int i = 0 ; i < iterations ; i++) {
		tot += times[i];
	}
	dummyMethod4();
	tot /= (double) iterations;
	printf("average duration for ordered: %f\n",tot);

	dummyMethod3();
	for (int i = 0 ; i < iterations ; i++) {
		int * arr = get_reversed(size);
		start();
		parallel_linear_search(arr, size, item);
		times[i] = end();
	}
	dummyMethod4();
	tot = 0;
	dummyMethod3();
	for (int i = 0 ; i < iterations ; i++) {
		tot += times[i];
	}
	dummyMethod4();
	tot /= (double) iterations;
	printf("average duration for reversed: %f\n",tot);
	
	dummyMethod3();
	for (int i = 0 ; i < iterations ; i++) {
		int * arr = get_random(size);
		start();
		parallel_linear_search(arr, size, item);
		times[i] = end();
	}
	dummyMethod4();
	tot = 0;
	dummyMethod3();
	for (int i = 0 ; i < iterations ; i++) {
		tot += times[i];
	}
	dummyMethod4();
	tot /= (double) iterations;
	printf("average duration for randomised: %f\n",tot);

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