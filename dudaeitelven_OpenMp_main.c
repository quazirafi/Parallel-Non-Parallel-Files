#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 =  *num2;
    *num2 = temp;
}

void OrderWithOmp (int SIZE)
{
    //int SIZE =1<<10;
    int A[SIZE];

dummyMethod3();
    for(int i=0; i<SIZE; i++)
    {
        A[i]=rand()%SIZE;
    }
dummyMethod4();

    int N = SIZE;
    int i=0, j=0;
    int first;
    double start,end;

//	start=omp_get_wtime();

    for( i = 0; i < N-1; i++ )
    {
        first = i % 2;

															dummyMethod1();
        #pragma omp parallel for default(none),shared(A,first,N)
        for( j = first; j < N-1; j += 1 )
        {
            if( A[ j ] > A[ j+1 ] )
            {
                swap( &A[ j ], &A[ j+1 ] );
            }
        }
															dummyMethod2();
    }

//    end=omp_get_wtime();

    // printf("\n-------------------------\n");
    // printf("Time with OMP  = %f",(end-start));
}

void OrderWithoutOmp (int SIZE)
{
    //int SIZE =1<<14;
    int A[SIZE];

    for(int i=0; i<SIZE; i++)
    {
        A[i]=rand()%SIZE;
    }

    int N = SIZE;
    int i=0, j=0;
    int first;
    double start,end;

    //clock_t inicio = clock();

    for( i = 0; i < N-1; i++ )
    {
        first = i % 2;

        for( j = first; j < N-1; j += 1 )
        {
            if( A[ j ] > A[ j+1 ] )
            {
                swap( &A[ j ], &A[ j+1 ] );
            }
        }
    }

//	for(i=0;i<N;i++)
//	{
//		printf(" %d",A[i]);
//	}

    //clock_t fim = clock();

    // printf("\n-------------------------\n");
    // printf("Time without OMP = %f",(fim-inicio));
}

int main (int argc, char *argv[])
{
    double   start= 0, stop =0;
    int size = 1000;

    start = omp_get_wtime();
    OrderWithOmp(size);
    stop = omp_get_wtime();


    printf("\n-------------------------\n");
    printf("Time with OMP  = %f",(stop-start));

    start= 0, stop =0;
    start = omp_get_wtime();
    OrderWithoutOmp(size);
    stop = omp_get_wtime();
    printf("\n-------------------------\n");
    printf("Time without OMP = %f",(stop-start));

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