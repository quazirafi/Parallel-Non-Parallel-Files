#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
  printf("Serial region.\n");

dummyMethod1();
  #pragma omp parallel for
  for (int i = 0; i < 20; i++) {
    printf("Hello %d\n", i);
  }
dummyMethod2();

  printf("Serial region.\n");
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