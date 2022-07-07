#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main() {
  unsigned int tab[1000000];
dummyMethod1();
  #pragma omp parallel for
  for (unsigned int i = 0; i < 1000000; ++i)
    for (unsigned int j = 0; j < 10000; ++j)
      tab[i] = j;

  return 0;
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