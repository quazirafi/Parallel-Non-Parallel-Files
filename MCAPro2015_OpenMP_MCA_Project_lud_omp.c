//#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//extern int omp_num_threads;
     int i,j,k;
     float sum;
float *a_g;
int size_g;

void lud_omp(float *a, int size)
{
    a_g=a;
    size_g = size;
//	 printf("num of threads = %d\n", omp_num_threads);
     for (i=0; i <size_g; i++){
//		omp_set_num_threads(omp_num_threads);
dummyMethod1();
#pragma omp parallel for default(none) \
         private(j,k,sum) shared(size_g,i,a_g) 
         for (j=i; j <size_g; j++){
             sum=a_g[i*size_g+j];
             for (k=0; k<i; k++) sum -= a_g[i*size_g+k]*a_g[k*size_g+j];
             a_g[i*size_g+j]=sum;
         }
dummyMethod2();
dummyMethod1();
#pragma omp parallel for default(none) \
         private(j,k,sum) shared(size_g,i,a_g) 
         for (j=i+1;j<size_g; j++){
             sum=a_g[j*size_g+i];
             for (k=0; k<i; k++) sum -=a_g[j*size_g+k]*a_g[k*size_g+i];
             a_g[j*size_g+i]=sum/a_g[i*size_g+i];
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