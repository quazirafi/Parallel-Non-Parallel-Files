#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "basic.h"

void basic_matmul(const int M, 
                  const double *A, const double *B, double *C)
{
    omp_set_num_threads(8);

    int i, j, k;
    double cij;
dummyMethod1();
    #pragma omp parallel for private(cij) collapse(2) schedule(static)
    for (j = 0; j < M; ++j)
    {
		for (i = 0; i < M; ++i)         
dummyMethod2();
        {
            cij = C[j*M+i];
            #pragma omp parallel for shared(cij)    
            for (k = 0; k < M; ++k)
            {
                cij += A[k*M+i] * B[j*M+k];
            }
            C[j*M+i] = cij;
        }
    }
    double check = 0.0;
dummyMethod3();
 	  for(j=0; j<M; j++)
 		  for(i=0; i<M; i++)
  			check+=C[j*M+i];
  	printf("%f\n", check);
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