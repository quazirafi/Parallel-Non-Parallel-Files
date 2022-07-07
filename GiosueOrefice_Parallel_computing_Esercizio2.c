#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*SOMMA DELLE RIGHE PARI DI UNA MATRICE  */

int main(int argc, char const *argv[])
{
	int mat[9][9],sum,sumTot=0,idThread,nThreads,i,j,resto,nloc;

	srand(time(NULL));

dummyMethod3();
	for (i = 0; i < 9; i++)
	{
		for(j=0;j<9;j++)
				mat[i][j]=1+rand()%10;
	
	}
dummyMethod4();

	


dummyMethod1();
	#pragma omp parallel for collapse(2) reduction(+:sumTot)
		for ( i = 0; i < 9; i+=2)
		{
			for (j = 0; j < 9; j++)
				sumTot+= mat[i][j];	
		}
dummyMethod2();

	printf("sumTot %d\n", sumTot);

	/* SEQUENZIALE
	sumTot=0;
	for ( i = 0; i < 9; i+=2)
		{
			for (j = 0; j < 9; j++)
			{
				
					sumTot+= mat[i][j];
					
				
			}
		}

	printf("sumTot %d\n", sumTot);

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