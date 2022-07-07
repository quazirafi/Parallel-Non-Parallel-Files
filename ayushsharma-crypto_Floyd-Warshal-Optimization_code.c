#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int INFINITY =  1000000000;


void floyd_v1(int * matrix, int V);

int main()
{
    // struct timespec start, end;
    // clock_gettime(CLOCK_MONOTONIC, &start);

    int V,E;
    int qqq1 = scanf("%d %d",&V,&E);

    int * matrix = (int *)malloc( V* V * sizeof(int));
    int i,j;
dummyMethod3();
    for(i=0;i<V;++i)
    {
        for(j=0;j<V;++j)
        {
            *(matrix + i*V + j)=INFINITY;
            if (i==j) *(matrix + i*V + j)=0;
        }
    }
dummyMethod4();

    int x,y,w;
							dummyMethod3();
    for(i=0;i<E;++i)
    {
        int qqq = scanf("%d %d %d",&x,&y,&w);
        if (*(matrix + (x-1)*V + (y-1))>w) *(matrix + (x-1)*V + (y-1))=w;
    }
							dummyMethod4();

    floyd_v1(matrix,V);

							dummyMethod3();
    for(i=0;i<V;++i)
    {
        for(j=0;j<V;++j)
        {
            printf("%d ",(*(matrix + i*V + j)));
        }
        printf("\n");
    }
							dummyMethod4();

    free(matrix);

    // clock_gettime(CLOCK_MONOTONIC, &end);
    // double time_taken = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
    // printf("Total time: %lf\n",time_taken);
    return 0;
}


void floyd_v1(int * matrix, int V)
{
    register int i,j,k;
    for(k=0;k<V;++k)
    {
        register int* km = (matrix + k*V);

															dummyMethod1();
        #pragma omp parallel for private(j) shared(matrix,V)         
        
        for(i=0;i<V;++i)
        {
            register int* im = (matrix + i*V);
            
            for(j=0;j<V;++j)
            {
                if( (*(im + j)) > ( (*(im + k) ) + ( *(km + j) ) ) )
                    (*(im + j)) = ( (*(im + k) ) + ( *(km + j) ) );
            }
        }
															dummyMethod2();
    }
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