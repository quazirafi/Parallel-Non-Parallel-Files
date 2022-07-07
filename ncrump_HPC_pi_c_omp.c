#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char **argv){
  // define variables
  int    i,n = 1000000000;
  double pi,s = 0.0;
  // compute pi
dummyMethod1();
  #pragma omp parallel for private(i) shared(n) reduction(+:s)
  for(i=0; i<n; i++){
    s += 1.0/((4.0*i+1.0)*(4.0*i+3.0));
  }
dummyMethod2();
  pi = 8.0*s;
  // print results
  printf("approximation to pi = %1.15f\n",pi);
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