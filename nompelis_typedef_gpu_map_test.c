// This is a small test-code to experiment with how the compiler interprets
// "typedef" variables when memory is mapped from the host to the (GPU) device.
// We have observed that in at least one case this code did not execute as
// expected when an array pointed to by a pointer that corresponds to a
// typedef-ed type was mapped to the device via OpenMP "target" off-loading.
// This code performs a sum of the two-double elements of two arrays. The steps
// are:
// 1. arrays to sum are built on the host
// 2. the correct result is computed on the host
// 3. the arrays and array to store the result are mapped to the device
// 4. the summation of the 0 and 1 "columns" is performed on the device
// 5. the result is brought back to the host from the device
// 6. the results are displayed
// Errors were found when the arrays are mapped to the device, by indicating
// the array start (as "0") and the number of elements. We expect that the type
// of element is as per the typedef, which is two doubles. When the error
// appears, the result stored in the array pointed to be "c" is incorrect.
// The mapping to the device seems to be interpreted as a single double per
// element of the array when the error appears. We control the size of this
// mapping with the variable "t", by setting it to "2", and get the correct
// result.
// Test-code written by Dr. Neil Mehta and Ioannis Nompelis, 2021/10/27.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef double s_t[2];

int main()
{
  int i, NE=10;

  printf( "Size of typdef variable: %d \n", (int) sizeof(s_t) );

  s_t* a = malloc(((size_t) NE) * sizeof(s_t));
  s_t* b = malloc(((size_t) NE) * sizeof(s_t));
  s_t* c = malloc(((size_t) NE) * sizeof(s_t));
  s_t* d = malloc(((size_t) NE) * sizeof(s_t));

			dummyMethod3();
  for(i=0;i<NE;i++)     // this sweep is executed on the host
  {
    a[i][0] = ((double) i)*1.0;
    a[i][1] = ((double) i)*2.0;
    b[i][0] = 0.5;
    b[i][1] = 0.7;
    c[i][0] = -9999.0;  // variable where result will be stored on the GPU
    c[i][1] = -9999.1;  // ...
    d[i][0] = a[i][0] + b[i][0];  // variable to store the correct answer
    d[i][1] = a[i][1] + b[i][1];  // ...
  }
			dummyMethod4();

  int t=1;     // variable to dictate in-device mapping size
#pragma omp target enter data map(to:a[0:t*NE], b[0:t*NE], c[0:t*NE]) 
			dummyMethod1();
#pragma omp target teams distribute parallel for
  for(i=0;i<NE;i++)    //  this sweep is performed in the (GPU) device
  {
    c[i][0] = a[i][0]+b[i][0];
    c[i][1] = a[i][1]+b[i][1];
  }
			dummyMethod2();

#pragma omp target exit data map(from:c[0:t*NE]) 

			dummyMethod3();
  for (i=0;i<NE;i++)
  {
    printf("Value of C[0] at %d is %f: correct value: %f\n",i,c[i][0],d[i][0]);
    printf("Value of C[1] at %d is %f: correct value: %f\n",i,c[i][1],d[i][1]);
  }
			dummyMethod4();
  
  free(a);
  free(b);
  free(c);
  free(d);

  printf("Code completed execution! \n");

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