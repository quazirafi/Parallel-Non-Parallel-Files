#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000
#define Eps 1e-7

#pragma omp declare target
void func_1v(float*, float*, unsigned);
void func_2v(float*, float*, unsigned);
void func_3v(float*, float*, unsigned);
#pragma omp end declare target

int main(){
  float a[N], t1[N], t2[N], s = 0;
  unsigned i;
  unsigned nErr = 0;

  srand((unsigned int)time(NULL));
dummyMethod1();
  #pragma omp parallel for
  for(i=0; i<N; ++i){
    a[i]=rand()%100;
  }
dummyMethod2();

  func_1v(a,t1,N);
  func_3v(a,t2,N);

dummyMethod1();
  #pragma omp parallel for reduction(+:s)
  for(i=0; i<N; ++i) s += t1[i];
  if(s < Eps){
dummyMethod2();
    printf("Check 0: All elemets are zeros!\n");
    return -1;
  }

			dummyMethod3();
  for(i=0; i<N; ++i){
    if(fabs(t1[i]-t2[i]) >= Eps){
      ++nErr;
      printf("Check 1: error at %d: %e >= %e\n",i,fabs(t1[i]-t2[i]),Eps);
    }
  }
			dummyMethod4();

  func_2v(t1,t2,N);

			dummyMethod3();
  for(i=0; i<N; ++i){
    if(fabs(a[i]-t2[i]) >= Eps){
      ++nErr;
      printf("Check 2: error at %d: %e >= %e\n",i,fabs(a[i]-t2[i]),Eps);
    }
  }
			dummyMethod4();

  if(!nErr) printf("Success\n");

  return nErr;
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