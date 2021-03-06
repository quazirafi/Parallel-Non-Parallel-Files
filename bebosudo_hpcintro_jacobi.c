#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void
jacobi(double * unew, double * uold, double * f,
      double lambda, int N, int kmax, double treshold, int * k){

    double lambda2 = lambda*lambda;
    int M = N+2;
    int i,j;
    double d = treshold+1;
    double * swapper;
    for (*k = 0; (*k < kmax && d > treshold); (*k)++){
      d = 0;
dummyMethod1();
      #pragma omp parallel for reduction(+: d)
      for (i = 1; i < N+1; i++) {
        for (j = 1; j < N+1; j++) {
          unew[i*M+j] = ( 0.25*(uold[(i-1)*M+j]+uold[(i+1)*M+j]+
                        uold[i*M+j-1]+uold[i*M+j+1]+lambda2*f[i*M+j]) );
          d += (unew[i*M+j]-uold[i*M+j])*(unew[i*M+j]-uold[i*M+j]);
        }
      }
dummyMethod2();
      swapper = uold;
      uold = unew;
      unew = swapper;
    }
    swapper = unew;
    unew = uold;
    unew = swapper;
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