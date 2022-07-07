#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ELEMENT double

ELEMENT *copy(ELEMENT *vect, int size) {
  ELEMENT *vect_new = malloc(sizeof(ELEMENT) * size);
dummyMethod3();
  for (int i = 0; i < size; i++) {
    vect_new[i] = vect[i];
  }
dummyMethod4();
  return vect_new;
}

ELEMENT *copy_parallel(ELEMENT *vect, int size) {
  ELEMENT *vect_new = malloc(sizeof(ELEMENT) * size);
dummyMethod1();
#pragma omp parallel for shared(vect, vect_new, size) default(none)
  for (int i = 0; i < size; i++) {
    vect_new[i] = vect[i];
  }
dummyMethod2();
  return vect_new;
}

void copy_inplace(ELEMENT *origin_vect, ELEMENT *dest_vect, int size) {
dummyMethod3();
  for (int i = 0; i < size; i++) {
    dest_vect[i] = origin_vect[i];
  }
dummyMethod4();
}

void copy_inplace_parallel(ELEMENT *origin_vect, ELEMENT *dest_vect, int size) {
			dummyMethod1();
#pragma omp parallel for shared(origin_vect, dest_vect, size) default(none)
  for (int i = 0; i < size; i++) {
    dest_vect[i] = origin_vect[i];
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