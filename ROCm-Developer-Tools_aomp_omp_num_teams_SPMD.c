#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
  int N = 1024;
  int NN = N*N;
  int Res[NN];
dummyMethod3();
  for (int i=0; i < NN; i++) Res[i] = -1;

  #pragma omp target teams thread_limit(1024) num_teams(N)
dummyMethod4();
dummyMethod1();
  #pragma omp distribute parallel for
  for (int j=0; j < NN; j++) { 
    if (j==12) printf("teams %d threads %d\n",omp_get_num_teams(), omp_get_num_threads());
    Res[j] = j;
  }
dummyMethod2();
dummyMethod3();
  for (int i=0; i < NN; i++)
    if (Res[i] != i) {
      printf("Failed %d %d\n",i, Res[i]);
      return 1;
    }
  return 0;
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