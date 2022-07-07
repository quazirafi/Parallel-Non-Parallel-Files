#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define size 4096

//using namespace std;

int main(int argc, char** argv)
{
    const int n = size;
    const int m = size;
    const int iter_max = 100;
    double error     = 1.0;
    
    double* data = (double*) malloc (sizeof(double)*n*m);
    double* temp = (double*) malloc (sizeof(double)*n*m);
    srand((unsigned)time(NULL));
        
dummyMethod3();
    for (int j = 0; j < n; j++)
    {
        for( int i = 1; i < m; i++ )
        {
        data[j*size+i] = rand()/(double)RAND_MAX;
        temp[j*size+i] = rand()/(double)RAND_MAX;
        }
    }
dummyMethod4();
    
    int iter = 0;
    printf("GPU OpenMP example, size:%d x %d, iter:%d \n",size,size,iter_max);
    double st = omp_get_wtime();
    while (iter < iter_max )
    {
        error = 0.0;
#pragma omp target map(to:temp) map(data,error)
	{
															dummyMethod1();
       #pragma omp parallel for reduction(max:error)
        for( int j = 1; j < n-1; j++)
        {
            for( int i = 1; i < m-1; i++ )
            {
                temp[j*size+i] = 0.25 * ( data[j*size+i+1] + data[j*size+i-1]
                                    + data[(j-1)*size+i] + data[(j+1)*size+i]);
                error = fmax( error, fabs(temp[j*size+i] - data[j*size+i]));
            }
        }
															dummyMethod2();
															dummyMethod1();
       #pragma omp parallel for  
        for( int j = 1; j < n-1; j++)
        {
            for( int i = 1; i < m-1; i++ )
            {
                data[j*size+i] = log(pow(2.7,pow(sin(pow(1.1,1.1)),1.1)+error))*temp[j*size+i];    
            }
        }
															dummyMethod2();

  }    
        
        iter++;
        //printf("%d \n",iter);
    }

    double et = omp_get_wtime();
 
    printf("total time: %f s\n", (et - st)); 
    free(data);
    free(temp);
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