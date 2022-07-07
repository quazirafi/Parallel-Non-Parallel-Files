#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){

  int i;
  double sum = 0;

dummyMethod1();
  #pragma omp parallel for private(i), reduction(+:sum) 
  for(i=0; i < 50; i++){
    sum += 1;
  }
dummyMethod2();

  printf("wynik: %f \n", sum);

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