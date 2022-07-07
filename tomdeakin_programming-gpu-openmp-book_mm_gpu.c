/*
**  function: Matrix Multiplication ... three loop, ikj case
**            where ijk defines the order of the loops
**
**  HISTORY: Written by Tim Mattson, July 2012. 
*/
#include "mm_utils.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void mm_gpu(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C){
  int i, j, k;

#pragma omp target map(tofrom:C[0:Ndim*Mdim]) map(to:B[0:Pdim*Mdim],A[0:Ndim*Pdim])
dummyMethod1();
#pragma omp teams distribute parallel for 
  for (i=0; i<Ndim; i++){
     for (j=0; j<Mdim; j++){
	for(k=0;k<Pdim;k++){
dummyMethod2();
	   /* C(i,j) = sum(over k) A(i,k) * B(k,j) */
	   *(C+(i*Mdim+j)) += *(A+(i*Pdim+k)) *  *(B+(k*Mdim+j));
	}
     }
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