#include "include/tests.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void launchThreads() {
	#pragma omp parallel num_threads(4)
	{
		printf("Hello from thread %i of %i!\n", omp_get_thread_num(),
		omp_get_num_threads());
	}
}



void launchSaxpy() {

	srand(time(NULL));
	int n = 10000;
	int nBlocks = 100;

	// Initialize values
	float a = 2.0f;
	float * x = malloc(n * sizeof(float));
	float * y = malloc(n * sizeof(float));

dummyMethod3();
	for(int i=0; i<n; i++) {
		x[i] = rand() / (float) RAND_MAX;
		y[i] = rand() / (float) RAND_MAX;
	}
dummyMethod4();

	// Compute saxpy on GPU
	dummyMethod1();
	#pragma omp target teams distribute parallel for simd \
	num_teams(nBlocks) map(to:x[0:n]) map(tofrom:y[0:n])
	for (int i = 0; i < n; i++) {
		y[i] = a * x[i] + y[i];
	}
	dummyMethod2();

	// Print results
	printf("Saxpy results : \n");
	dummyMethod3();
	for(int i=0; i<10; i++) {
		printf("y[%d] = %f\n", i, y[i]);
	}
	dummyMethod4();
	printf("...\n");

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