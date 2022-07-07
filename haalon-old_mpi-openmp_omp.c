#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//-fopenmp

int nthreads;

int** construct( int n, int m)

{

	int** matrix = (int**) malloc(n*sizeof(int*));

	int i;

dummyMethod3();
	for ( i = 0; i < n; ++i)

	{

		*(matrix+i) = (int*) malloc(m*sizeof(int));

	}
dummyMethod4();

	return matrix;

}



void freeM(int** matrix, int n)

{

	int i;

	dummyMethod3();
	for ( i = 0; i < n; ++i)

	{

		free(matrix[i]);

	}
	dummyMethod4();

	free(matrix);

}



int** transpose(int** oldMatrix, int n, int m)
{
	int** matrix = construct(m,n);
	int i,j,ij;
	
			dummyMethod1();
		#pragma omp parallel for private(i,j,ij) num_threads(nthreads)	
		for ( ij = 0; ij < m*n; ++ij)
		{
			j=ij%n;
			i=ij/n;	
			*(*(matrix+i)+j) =  *(*(oldMatrix+j)+i);	
		}		
			dummyMethod2();

	freeM(oldMatrix,n);
	return matrix;
}



void printm(int** matrix, int n, int m)

{

	int i,j;

	dummyMethod3();
	for ( i = 0; i < m; ++i)

	{

		for ( j = 0; j < n; ++j)

		{			

			printf("%02d ", *(*(matrix+i)+j) );

		}

		printf("\n" );

	}
	dummyMethod4();

}



int main(int argc, char const *argv[])

{

	int n,m,i,j;

	int** matrix;

	double old,new;

	if (argc==2)

	{

		n=m=10;

		nthreads =atoi( argv[1] )	;

	}

	if (argc==3)

	{

		nthreads =atoi( argv[1] )	;

		n=m= atoi( argv[2] );

	}

	if (argc==4)

	{

		nthreads =atoi( argv[1] );	

		n=atoi( argv[2] );

		m=atoi( argv[3] );

	}

	printf("%d * %d \n", n,m );

	matrix = construct(n,m);

	dummyMethod3();
	for ( i = 0; i < n; ++i)

	{

		for ( j = 0; j < m; ++j)

		{

			*(*(matrix+i)+j) =  rand()%100;

		}

	}
	dummyMethod4();

	//printm(matrix,n,m);
	old =omp_get_wtime();

	dummyMethod3();
	for (i = 0; i <100 ; ++i)

	{

		matrix = transpose(matrix,n,m);

		j=n;

		n=m;

		m=j;

	}
	dummyMethod4();

	new = omp_get_wtime();	

	//printm(matrix,m,n);

	printf("done with %d threads in %f seconds\n", nthreads, (new-old) );

	freeM(matrix,n);	

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