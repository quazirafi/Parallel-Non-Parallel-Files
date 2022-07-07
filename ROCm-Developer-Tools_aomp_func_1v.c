#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void func_1v(float* in, float* out, unsigned n){
  unsigned i;
dummyMethod1();
  #pragma omp target teams distribute parallel for map(to: in[0:n]) map(from: out[0:n])
  for(i=0; i<n; ++i){
    out[i]=2*in[i];
  }
dummyMethod2();
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