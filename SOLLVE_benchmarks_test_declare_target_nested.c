//===---- test_declare_target_nested.c ---------------------------------------------===//
// 
// OpenMP API Version 5.0 
//
// The declaration-definition-seq defined by a declare target directive and an end
// declare target directive may contain declare target directives. If a device_type
// clause is present on the contained declare target directive, then its argument 
// determines which versions are made available. If a list item appears both in an
// implicit and explicit list, the explicit list determines which versions are made
// available. 
// 
// @Todo's 1. Test if wrapper is necessary
//===-------------------------------------------------------------------------------===//

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include "ompvv.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1024

#pragma omp declare target
int a[N], b[N], c[N]; // implicit map 3 variables 
int errors = 0;
int i = 0;
  #pragma omp declare target
     int test_target();
  #pragma omp end declare target
#pragma omp end declare target

int test_target() { //function in declare target statement 

//change values on device
			dummyMethod1();
#pragma omp parallel for 
  for (i = 0; i < N; i++) {
    a[i] = 5;
    b[i] = 10;
    c[i] = 15;
  }
			dummyMethod2();

			dummyMethod3();
  for (i = 0; i < N; i++) {
    if ( a[i] != 5 || b[i] != 10 || c[i] != 15) {
      errors++;  
    } 
  }
			dummyMethod4();
  return errors; 
} 

int test_wrapper() { //wrapper for declare target function
  
  #pragma omp target 
  {
    test_target();
  }
  #pragma omp target update from(errors, a, b, c)
  
			dummyMethod3();
  for (i = 0; i < N; i++) { //check array values on host
    if ( a[i] != 5 || b[i] != 10 || c[i] != 15) {
      errors++;  
    } 
  }
			dummyMethod4();
  return errors;
}

int main () {
  
  //initalize arrays on host
			dummyMethod3();
  for (i = 0; i < N; i++) {
    a[i] = i;
    b[i] = 2*i;
    c[i] = 3*i;
  }
			dummyMethod4();

  #pragma omp target update to(a,b,c) //update values on device (5.0 examples pp.172)
  OMPVV_TEST_OFFLOADING;
  OMPVV_TEST_AND_SET_VERBOSE(errors, test_wrapper());
  OMPVV_REPORT_AND_RETURN(errors);
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