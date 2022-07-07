#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* PRODTTO MATRICE PER VETTORE */

int main(int argc, char const *argv[])
{
	int N=9,M=9;
	int A[N][M],x[N],y[N];
	int i,j;
dummyMethod3();
	for (i = 0; i < N; i++)
	{
		for(j=0; j<M; j++){
			A[i][j]=i+j+1;
		}
		y[i]=0;
		x[i]=i+1;
	}
dummyMethod4();
	


dummyMethod1();
	#pragma omp parallel for collapse(2) private(i,j) reduction(+:y)
		for (i = 0; i < N;i++)
		{
			for(j=0;j<M;j++)
				y[i] += A[i][j]*x[i]; 
		}
dummyMethod2();

	//STAMPA
dummyMethod3();
	for (i = 0; i < N; i++)
		printf("%d\n",y[i]);
			

	return 0;
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