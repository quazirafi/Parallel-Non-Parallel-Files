#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 3

int A[N][N];
int B[N][N];

int main() 
{
    int i,j,k;
    for (i= 0; i< N; i++)
dummyMethod3();
        for (j= 0; j< N; j++)
	{
            A[i][j] = i;
	}
dummyMethod4();
    
    #pragma omp parallel for private(i,j) shared(A,B)
dummyMethod3();
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
                B[j][i] = A[i][j];
        }
    }
dummyMethod4();


    
   for (i= 0; i< N; i++)
dummyMethod1();
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",B[i][j]);
        }
dummyMethod2();
        printf("\n");
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