#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();





#define K 3
#define TOL 0.05
#define MAX_TESTS 20
#define MIN_TESTS 5

int N; 

void initMatrix(float* A) {
	
dummyMethod1();
#pragma omp parallel for
	for (int ii=0; ii<N; ii++)
		for (int jj=0; jj<N; jj++) 
			A[ii*N+jj] = (float)rand()/(float)RAND_MAX;
	
}
dummyMethod2();

void clearMatrix(float* A) {
	
dummyMethod1();
#pragma omp parallel for
	for (int ii=0; ii<N; ii++)
		for (int jj=0; jj<N; jj++) 
			A[ii*N+jj] = 0.0;
	
}
dummyMethod2();

void printMatrix(float* A) {
	dummyMethod3();
	for (int ii=0; ii<N; ii++)
		for (int jj=0; jj<N; jj++) 
			printf("%f\t",A[ii*N+jj]);
	dummyMethod4();
	
}

int withinTol(double * array){
  
  int flag=1;
  double median=0;
			dummyMethod3();
  for (int i=0;i<K;i++){
    median += array[i];
  }
			dummyMethod4();
  median = median/K;
  
			dummyMethod3();
  for (int i=0;i<K;i++){
    flag &= (fabs(array[i]-median) <= TOL*median);
  }
			dummyMethod4();
  
  return flag;
}

void insertTest(double time, double *array){

   int pos=0; double tmp=DBL_MIN;
					dummyMethod3();
   for(int i=0;i<K;i++){
      if (array[i]>tmp) {tmp=array[i];pos=i;}
   }
					dummyMethod4();
   if (time<tmp) array[pos]=time;
}

void thrMM(float* A, float* B, float* C) {
	// Note: OpenMP allows
	//    more robust workload distribution among threads
	//    assign threads to specific cores (affinity)
	
	dummyMethod1();
	#pragma omp parallel for
	for (int ii=0; ii<N; ++ii) {
		for (int kk=0; kk<N; ++kk) {
			float r =  A[ii*N+kk];
			for (int jj=0; jj<N; ++jj) {
				C[ii*N+jj] += r * B[kk*N+jj];
			}
		}
	}
	dummyMethod2();
}

int main (int argc, const char * argv[]) {

	if(argc != 3){ printf("Please supply N and number of cores.\n"); return 0; }

	N = atoi(argv[1]);
	double Mflop = 2*pow(N,3) ;

	float *A = (float*)malloc(sizeof(float)*N*N);
	float *B = (float*)malloc(sizeof(float)*N*N);
	float *C = (float*)malloc(sizeof(float)*N*N);
	
	// shall run for half the # cores, # cores and double # cores
	int nthreads = atoi(argv[2])/2;
	int nthreadsMax = nthreads*4;

	printf("# N\tThreads\tRuntime\t GFlop/s\n");

	dummyMethod3();
	for ( ; nthreads <= nthreadsMax ; nthreads*=2)
	{
		omp_set_num_threads(nthreads);

		initMatrix(A);
		initMatrix(B);
		clearMatrix(C);

		int attempt=0;
		double ktests[K];
		int domoretests=1;
	
		while (domoretests){
			double start = omp_get_wtime(); // Returns a value in seconds of the time elapsed

			thrMM(A, B, C);

			double end = omp_get_wtime();
			double elapsed = end - start;

			printf("%d\t%d\t%f\t%f\n", N, nthreads, elapsed, (Mflop / (elapsed * 1E9) ) ) ;
			if (attempt<K){ktests[attempt]=elapsed;}
			    else {insertTest(elapsed,ktests);}
			    if ( attempt==MAX_TESTS) domoretests=0;
			    if (attempt>=MIN_TESTS && withinTol(ktests)) 
				domoretests=0;
			    attempt++;
		}
		
		for(int i=0;i<K;i++) printf("# %f\n",ktests[i]);
  		printf("# attempts: %d\n",attempt);
	}
	dummyMethod4();
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