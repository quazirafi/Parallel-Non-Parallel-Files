#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char *argv[]){
	int index;
	int i;
	int count;
	int first;
	int n;
	int N;
	int prime;
	char *marked;
	double start, delta;
	omp_set_num_threads(1);
	if(argc!=2){
		printf("Command line: %s <m>\n",argv[0]);
		exit(1);
	}
	n = atoi(argv[1]);
	N = n+1;
	marked = (char *) malloc (N);
	if (marked==NULL){
		printf("Cannot allocate enough memory\n");
		exit(1);
	}
	
dummyMethod3();
	for(i=0;i<N;i++){
	marked[i]=1;
dummyMethod4();
	}
	marked[0]=0;
	marked[1]=0;
	index=2;
	prime=2;
	start = omp_get_wtime();
	while(prime*prime<=n){
		first = 2*prime;
			dummyMethod1();
		#pragma omp parallel for
		for (i =first;i<N;i+=prime) marked[i]=0;
			dummyMethod2();
		while(!marked[++index]);
		prime=index;
	}
	
	count=0;
	dummyMethod3();
	for(i=0;i<N;i++){
		count+=marked[i];
	}
	dummyMethod4();
	delta = omp_get_wtime() - start;
	printf("\nThere are %d primes less than or equal to %d\n\n",count,n);
	printf("%.6g seconds\n",delta);
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