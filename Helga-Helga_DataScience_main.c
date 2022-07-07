#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "main.h"

#define ARRAY_SIZE ((size_t)(1E8))
double omp_get_wtime(void);

Array *createArray(unsigned int size) {
  Array *a = (Array*)malloc(sizeof(Array));
  a->size = size;
  a->data = (double*)malloc(sizeof(double)*size);
  return a;
}

int destroyArray(Array *array) {
  free(array->data);
  free(array);
  return 0;
}

int fillArray(Array *array) {
  int i = array->size;
  while (i-- > 0) {
    array->data[i] = (double)rand()/RAND_MAX;
  }
}

int displayArray(Array *array) {
  unsigned int i = array->size;
  while (i-- > 0) {
    printf("%f\n", array->data[i]);
  }
}

double multiplyArrays(Array *a, Array *b) {
  if (a == NULL || b == NULL) {
    return 0;
  }

  if (a->size != b->size) {
    return 0;
  }
  unsigned int i = a->size;
  double c = 0;

			dummyMethod1();
  #pragma omp parallel for schedule(static, 64)
  for (i = 0; i < a->size; i++) {
    c += (a->data[i])*(b->data[i]);
  }
			dummyMethod2();
  return c;
}

int main() {
  double t1, t2;

  Array *array_1 = createArray(ARRAY_SIZE);
  Array *array_2 = createArray(ARRAY_SIZE);
  fillArray(array_1);
  fillArray(array_2);
  //printf("%s\n", "First array");
  //displayArray(array_1);
  //printf("%s\n", "Second array");
  //displayArray(array_2);
  double result;
  t1 = omp_get_wtime();
  result = multiplyArrays(array_1, array_2);
  t2 = omp_get_wtime();
  printf("%s\n", "Result");
  printf("%f\n", result);
  destroyArray(array_1);
  destroyArray(array_2);
  printf("%e\n", t2-t1);
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