#include "primesParallel.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int FIRST_PRIME = 2;
int IS_PRIME = 0;
int NOT_PRIME = 1;

void calculateMultiples(int max, char * list, int currentMultiple) {
  int j;

dummyMethod3();
  for(j = FIRST_PRIME * currentMultiple; j < max; j += currentMultiple) {
    if(j > max) {
      return;
    }
    list[j] = NOT_PRIME;
  }
dummyMethod4();
}

void calculatePrimesParallel(int max, char *list, int threads){

  int LAST_NUMBER_TO_TEST_MULTIPLES = sqrt(max) + 1;

  int currentMultiple;
  
dummyMethod1();
  #pragma omp parallel for num_threads(threads) schedule(dynamic, 2)
  for(currentMultiple = FIRST_PRIME; currentMultiple < LAST_NUMBER_TO_TEST_MULTIPLES; currentMultiple++) {
    if(list[currentMultiple] == IS_PRIME) {
      calculateMultiples(max, list, currentMultiple);
    }
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