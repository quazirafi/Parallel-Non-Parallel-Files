#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*
**  function: Matrix Multiplication ... three loop, ikj case
**            where ijk defines the order of the loops
**
**  HISTORY: Written by Tim Mattson, July 2012. 
*/

void mm_ikj_par(int Ndim, int Mdim, int Pdim, double *A, double *B, double *C){
  int i, j, k;

dummyMethod1();
  #pragma omp parallel for private(i,j,k) 
  for (i=0; i<Ndim; i++){
	for(k=0;k<Pdim;k++){
dummyMethod2();
     for (j=0; j<Mdim; j++){
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