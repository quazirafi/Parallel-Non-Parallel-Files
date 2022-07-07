#include "omp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SEED 26

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <positive number>\n", argv[0]);
    return 1;
  }

  uint64_t i, n = strtoul(argv[1], NULL, 0), result = 0;
  uint8_t *a = malloc(n * sizeof(uint8_t)), *b = malloc(n * sizeof(uint8_t));
  srandom(SEED);

dummyMethod3();
  for (i = 0; i < n; ++i) {
    a[i] = random() % 100;
    b[i] = random() % 100;
  }
dummyMethod4();

dummyMethod1();
#pragma omp parallel for shared(a, b) reduction(+ : result)
  for (i = 0; i < n; ++i) {
    result += (a[i] < b[i]);
  }
dummyMethod2();

  free(a);
  free(b);

  printf("a[i] < b[i] %ld times\n", result);
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