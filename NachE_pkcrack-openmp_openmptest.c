#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	const int size = 256;
	double sinTable[size];
	int this_thread, num_threads;

dummyMethod1();
	#pragma omp parallel for
	for(int n=0; n<size; ++n){
		num_threads = omp_get_num_threads();
		this_thread = omp_get_thread_num();
		printf ("%d/%d   %d\n",this_thread, num_threads, n);
	}
dummyMethod2();
  
    // the table is now initialized
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