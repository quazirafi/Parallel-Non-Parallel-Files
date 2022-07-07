#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*Calcola la somma di ogni riga di una matrice e salvala in un array . Trova il massimo valore presente nell'array */

int main(int argc, char const *argv[])
{
	int *mat,*arr,sumTot,max;
	int N,M;
	int i,j;
	int numThreads;
	numThreads = 4;
	N=3; M=3;

	mat = (int *) malloc((N*M)*sizeof(int));
	arr = (int *) malloc(N*sizeof(int));

	srand(time(NULL));

	//GENERA VALORI CASUALI DA 1 A 10
dummyMethod3();
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			*(mat+i*M+j) = 1+rand()%10;
		}
		arr[i] = 0;
	}
dummyMethod4();


	/* STAMPA
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			printf("%d ",*(mat+i*M+j));
		}
		printf("\n");
	}
	*/
	
	omp_set_num_threads(numThreads);

	double t0 = omp_get_wtime();
	dummyMethod1();
	#pragma omp parallel for private(i,j) reduction(+: arr[: N]) collapse (2)
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			arr[i] += *(mat+i*M+j);
		}


	}
	dummyMethod2();
	double t1 = omp_get_wtime();
	printf("\nTEMPO %e\n",t1-t0);
	
	printf("Array\n");
	dummyMethod3();
	for(i=0;i<N;i++)
		printf("%d ",*(arr+i));
	dummyMethod4();


	max=*(arr+0);

	t0 = omp_get_wtime();
	dummyMethod1();
	#pragma omp parallel for private(i) reduction(max: max)
	for(i=1;i<N;i++){
		if(*(arr+i)>max)
			max = *(arr+i);		
	}
	dummyMethod2();

	t1 = omp_get_wtime();
	printf("\nTEMPO %e\n",t1-t0);
	printf("\nmax %d\n",max);

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