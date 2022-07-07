#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DIM 3


void data_rearrangement(float *Y, float *X,unsigned int *permutation_vector,int N){
	
if(N>200000)
 { 
	
dummyMethod1();
#pragma omp parallel for shared(X,Y,permutation_vector,N) schedule(static)
  for(int i=0; i<N; i++)
  {                                                      
      memcpy(&Y[i*DIM], &X[permutation_vector[i]*DIM], DIM*sizeof(float));//η memcpy(α,β,γ) αντιγραφει τους πρωτους γ χαρακτηρες του β στο α
  }
dummyMethod2();

}
else {
dummyMethod3();
for(int i=0; i<N; i++)
  {                                                      
      memcpy(&Y[i*DIM], &X[permutation_vector[i]*DIM], DIM*sizeof(float));//η memcpy(α,β,γ) αντιγραφει τους πρωτους γ χαρακτηρες του β στο α
  }

 }
}
dummyMethod4();
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