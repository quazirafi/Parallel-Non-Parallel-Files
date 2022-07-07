#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 3
#define M 4

int main(int argc, char const *argv[])
{
	int *A,*a,*b,alfa,beta,*r;
	int i,j;
	
	A = (int *) malloc((M*N)*sizeof(int));
	a = (int *) malloc(M*sizeof(int));
	b = (int *) malloc(N*sizeof(int));
	r = (int *) malloc(M*sizeof(int));


	srand(time(NULL));

	alfa=1+rand()%10;
	beta=1+rand()%10;

dummyMethod3();
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			*(A+i*N+j) = rand()%10;
			b[j] = j+3;
		}
		a[i] = i+1;
		r[i]=0;
	}
dummyMethod4();

	dummyMethod1();
	#pragma omp parallel for private(i,j) reduction(+: r[:M])
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			r[i] += alfa*A[i*N+j] * b[j];
		}
		r[i] += beta * a[i];
	}
	dummyMethod2();

	long p=1;
			dummyMethod1();
	#pragma omp parallel for private(i) reduction(*:p)
		for(i=0;i<M;i++)
			p *= r[i];
			dummyMethod2();
	
	printf("RISULTATI\nR[]:\n");
	dummyMethod3();
	for(i=0;i<M;i++)
		printf("%d\n",r[i]);
	dummyMethod4();
	
	printf("P = %ld\n",p);
	printf("\n");


/*
printf("RISULTATI SEQUENZIALE\n");
p=1;
for(i=0;i<M;i++){
	r[i] = 0;
		for(j=0;j<N;j++){
			r[i] += alfa*A[i*N+j] * b[j];
		}
		r[i] += beta * a[i];
	}

	for(i=0;i<M;i++)
			p *= r[i];

	for(i=0;i<M;i++)
		printf("%d\n",r[i]);
	printf("%ld\n",p);

*/
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