/*
   Standard implementation of the Floyd-Warshall Algorithm
	 using OpenMP parallel for.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "util.h"
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

inline int min(int a, int b);

int main(int argc, char **argv)
{
	int **A;
	int i,j,k;
	struct timeval t1, t2;
	double time;
	int N=1024;

	if (argc != 2) {
		fprintf(stdout,"Usage: %s N\n", argv[0]);
		exit(0);
	}

	N=atoi(argv[1]);

	A = (int **) malloc(N*sizeof(int *));
dummyMethod3();
	for(i=0; i<N; i++) A[i] = (int *) malloc(N*sizeof(int));

	graph_init_random(A,-1,N,128*N);
dummyMethod4();

	gettimeofday(&t1,0);
	for(k=0;k<N;k++)
			dummyMethod1();
		#pragma omp parallel for private(i, j) shared(A, k, N)
		for(i=0; i<N; i++)
			for(j=0; j<N; j++)
				A[i][j]=min(A[i][j], A[i][k] + A[k][j]);
			dummyMethod2();

	gettimeofday(&t2,0);

	time=(double)((t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec)/1000000;
	printf("FW,%d,%.4f\n", N, time);

	/*
	   for(i=0; i<N; i++)
	   for(j=0; j<N; j++) fprintf(stdout,"%d\n", A[i][j]);
	 */

	return 0;
}

inline int min(int a, int b)
{
	if(a<=b)return a;
	else return b;
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