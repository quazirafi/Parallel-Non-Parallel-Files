#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARRAY_SIZE 10
#define NUM_THREADS 6

int main (int argc, char *argv[]) 
{
	int * a;
	int * b; 
	int * c;
        int n = ARRAY_SIZE;
	int n_per_thread;
	int total_threads = NUM_THREADS;
	int i;
        
        a = (int *) malloc(sizeof(int)*n);
	b = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);

dummyMethod3();
        for(i=0; i<n; i++) {
            a[i] = i;
        }
dummyMethod4();
dummyMethod3();
        for(i=0; i<n; i++) {
            b[i] = i;
        }   
dummyMethod4();

	omp_set_num_threads(total_threads);
	
	n_per_thread = n/total_threads;
	
															dummyMethod1();
	#pragma omp parallel for shared(a, b, c) private(i) schedule(static, n_per_thread)
        for(i=0; i<n; i++) {
		c[i] = a[i]+b[i];
		printf(" -> Thread %d is working on the Element %d\n", omp_get_thread_num(), i);
        }
															dummyMethod2();

	printf("\ti\ta[i]\t+\tb[i]\t=\tc[i]\n");
															dummyMethod3();
        for(i=0; i<n; i++) {
		printf("\t%d\t%d\t\t%d\t\t%d\n", i, a[i], b[i], c[i]);
        }
															dummyMethod4();
	
        free(a);  free(b); free(c);
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