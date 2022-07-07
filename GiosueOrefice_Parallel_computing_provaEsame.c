#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
	Scrivere un programma parallelo per l'ambiente QUAD-CORE con p=4.
	IL core master deve definire una matrice A di dimensione NxN = 8x8 le cui entrate sono casualmente generate 
	in un intervallo [2,7]. 
	QUindi ogni core deve sommare tra loro gli elementi di un blocco quadrato della matrice A di dimensione N/2xN/2,
	conservando i valori in un vettore B di dimensione N/2 = 4.
	Infine, i core devono collaborare per calcolare la somma finale tra gli elementi di tale vettore B.
*/


void stampa (int *mat,int N,int numThreads);
int main(int argc, char const *argv[])
{
	int *mat,*B,sumTot=0;
	int N;
	int i,j;
	int numThreads;
	numThreads = 4;
	N=8;
	mat = (int *) malloc((N*N)*sizeof(int));	
	B = (int *) malloc(numThreads*sizeof(int)); //Da traccia dovrebbe essere N/2 ma poi va bene solo se N=8;
	srand(time(NULL));

	//GENERA VALORI CASUALI DA 2 A 7 e stampa
	dummyMethod3();
	for(i=0;i<N;i++){
		
		for(j=0;j<N;j++){
			*(mat+i*N+j) = 2+rand()%6;
			//printf("%d ", *(mat+i*N+j));
		}		
		
	}
	dummyMethod4();

	dummyMethod3();
	for(i=0;i<numThreads;i++)
		B[i] = 0;
	dummyMethod4();

	stampa(mat,N,numThreads);


	printf("\n");
	int id,nloc,nlocTot,step;

	omp_set_num_threads(numThreads);

	#pragma omp parallel private(id,nloc,i,j,nlocTot,step) reduction(+: B[: numThreads])
	{
		nlocTot = (N*N)/numThreads;
		nloc = (int) nlocTot/(N/2); //bisogna fare la radice quadrata
		id = omp_get_thread_num();
		
		if(id%2 == 0)
			step = id*nlocTot;
		else 
			step = (id-1)*nlocTot+nloc;

			dummyMethod3();
		for(i=0;i<nloc;i++){
			for(j=0;j<nloc;j++){
				B[id]+=*(mat+(i*N+j)+step);
				printf("indice %d  id %d valore %d\n", (i*N+j)+step, id,*(mat+(i*N+j)+step));
			}
		}
			dummyMethod4();

	}
	printf("\nARRAY\n");
	dummyMethod3();
	for(i=0;i<numThreads;i++)
			printf("%d  ",B[i]);
	dummyMethod4();

			dummyMethod1();
	#pragma omp parallel for private(i) reduction(+:sumTot)
		for(i=0;i<4;i++){
			sumTot+=B[i];
	
		}
			dummyMethod2();

		printf("\nsum %d\n",sumTot);

}


void stampa (int *mat,int N,int numThreads){

	printf("\n");
	int i,j;
	dummyMethod3();
	for(i=0;i<N;i++){
		if(i==(N*N)/numThreads/(N/2))
				printf("\n");
		for(j=0;j<N;j++){
			if(j==(N*N)/numThreads/(N/2))
				printf("\t");
			printf("%d ", *(mat+i*N+j));
		}
		printf("\n");
		

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