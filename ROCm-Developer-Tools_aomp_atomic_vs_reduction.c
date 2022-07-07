#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main() {
//
//  atomic_vs_reduction.c: This test shows how much faster reductions are than atomic operations 
//
  int main_rc = 0;
  int N       = 5001;
  double expect = (double) (((double)N-1)*(double)N)/2.0;

  double a    = 0.0;
  double t0 = omp_get_wtime();
  #pragma omp target teams distribute parallel for map(tofrom:a)
dummyMethod3();
  for(int ii = 0; ii < N; ++ii) {
    #pragma omp atomic
    a+=(double)ii;;
  }
dummyMethod4();
  double t1 = omp_get_wtime()-t0;
  if (a == expect) {
    printf("Success atomic    sum of %d integers is: %f in %f secs\n",N,a,t1);
  } else {
    printf("FAIL ATOMIC SUM N:%d result: %f != expect: %f \n", N,a,expect);
    main_rc=1;
  }

  // Now do the sum as a reduction
  double ra = 0.0;
  double t2 = omp_get_wtime();
dummyMethod1();
  #pragma omp target teams distribute parallel for reduction(+:ra) 
  for(int ii = 0; ii < N; ++ii) {
    ra+=(double)ii;;
  }
dummyMethod2();
  double t3 = omp_get_wtime() - t2;

  if (ra == expect) {
    printf("Success reduction sum of %d integers is: %f in %f secs\n",N,ra,t3);
  } else {
    printf("FAIL REDUCTION SUM N:%d result: %f != expect: %f \n", N,ra,expect);
    main_rc=1;
  }
  return main_rc;
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