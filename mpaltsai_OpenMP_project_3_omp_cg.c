#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double gettime(void)
{
	struct timeval ttime;
	gettimeofday(&ttime , NULL);
	return ttime.tv_sec + ttime.tv_usec * 0.000001;
}

int main(int argc, char ** argv)
{
	double timeTotal = 0.0f;
	double time0=gettime();
	
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int l = atoi(argv[3]);
	int threads = atoi(argv[4]);

	unsigned long long checksum = 0; 
	
	srand(0);
	
	//memory allocation for m,n sets	
	int ** mset = (int**)malloc(sizeof(int*)*m);
	assert(mset!=NULL);
	
	int ** nset = (int**)malloc(sizeof(int*)*m);
	assert(nset!=NULL);
	
	dummyMethod3();
	for(int ki=0; ki<m; ki++){
		//allocate memory for each string
		mset[ki] = (int*)malloc(sizeof(int)*l);
		nset[ki] = (int*)malloc(sizeof(int)*l);

		
		for(int kj=0; kj<l; kj++){
			//initialize strings with random values
			mset[ki][kj] = (int)(rand()%2);
			nset[ki][kj] = (int)(rand()%2);
			
		}
	}
	dummyMethod4();
	
	
	//memory allocation for a m*n matrix so as to store Hamming distances from string comparison
	unsigned long long ** mn = (unsigned long long**)malloc(sizeof(unsigned long long*)*m);
	assert(mn!=NULL);
	
	dummyMethod3();
	for(int i=0; i<m; i++){

		mn[i] = (unsigned long long*)malloc(sizeof(unsigned long long)*m); 
	}
	dummyMethod4();

	
	

	//pairwise string comparison to compute Hamming distance and write it to mn matrix

	omp_set_num_threads(threads);

	
	int i;
	dummyMethod1();
	#pragma omp parallel for
	for(i=0; i<m; i++){
		
		for(int j=0; j<n; j++){
			
			unsigned long long d = 0; 
			
			for(int k=0; k<l; k++){

				if(mset[i][k] != nset[j][k])
					d += 1;
				else
					d += 0;				
			}
			
			mn[i][j] = d; 

		}
		
	}
	dummyMethod2();

	/*-----------3rd parallel implementation--------*/
	
	//calculate the sum of Hamming distances stored in mn matrix

	omp_get_thread_num();

	int k;
	
	unsigned long long* partialSumVector = (unsigned long long*)malloc(sizeof(unsigned long long)*threads);
	assert(partialSumVector!=NULL);

	dummyMethod3();
	for(k=0;k<threads;k++){
		partialSumVector[k] = 0;
	}
	dummyMethod4();

	dummyMethod1();
	#pragma omp parallel for collapse(2)
	for(k=0;k<m;k++){
		for(int j=0;j<n;j++){
		partialSumVector[omp_get_thread_num()] += mn[k][j];
		//printf("partialSum is %d", partialSumVector[omp_get_thread_num()]);
		}
	}
	dummyMethod2();

	//printf("initial checksum is %lld\n", checksum);
	dummyMethod3();
	for(k=0;k<threads;k++){
	  //printf("thread %d has partialSumVector %lld\n", k,partialSumVector[k]);
	  //printf("checksum before the addition is %lld\n", checksum);
		checksum +=partialSumVector[k];
		
		//printf("checksum now is %lld\n", checksum);
	}
	dummyMethod4();

	
	printf("Checksum is %lld\n", checksum);
	
	double time1=gettime();
	timeTotal += time1-time0;
	
	printf("Time %f\n", timeTotal);
	
	free(mset);
	free(nset); 
	free(mn);
	free(partialSumVector);
	
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