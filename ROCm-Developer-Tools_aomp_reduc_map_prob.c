#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N 5000000

int main(){
  double *B,  *C;

  B = (double*)malloc(sizeof(double) * N);
  C = (double*)malloc(sizeof(double) * N);

dummyMethod3();
  for(int i = 0; i < N; i++){
    B[i] = 1.0;
    C[i] = 1.0;
  }
dummyMethod4();

  double sum = 0;
  
  #pragma omp target data map(to:B[0:N], C[0:N])
dummyMethod1();
  #pragma omp target teams distribute parallel for reduction(+:sum) map(tofrom:sum)
  for(int i = 0; i < N; i++)
    sum += B[i] * C[i];

    printf("SUM = %f\n", sum);
  if (sum != N){
dummyMethod2();
    printf("Failed!\n");
    return -1;
  } else{
    printf("SUCCESS!\n");
  }
  
  free(B);
  free(C);

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