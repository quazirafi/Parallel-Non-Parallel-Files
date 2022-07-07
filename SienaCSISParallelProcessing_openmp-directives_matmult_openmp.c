/* 
   Matrix multiplication example

   OpenMP version

   Jim Teresco, CS 338, Williams College, CS 341, Mount Holyoke College
   Mon Feb 10 10:55:31 EST 2003
   
   Updated for CSIS-335, Siena College, Fall 2021
*/

/* header files needed for printf, gettimeofday, struct timeval */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* header file for our own timer.c function diffgettime */
#include "timer.h"

/* we will multiply square matrices, how big? */
#define SIZE 1500

/* our matrices */
double a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE];

/* it's a simple program for now, we'll just put everything in main */
int main(int argc, char *argv[]) {

  /* counters */
  int i, j, k;
  double sum;

  /* to pass to gettimeofday to get wall clock times */
  struct timeval start, stop;

  /* initialize and allocate matrices, just fill with junk */
  gettimeofday(&start, NULL);
			dummyMethod3();
  for (i=0; i<SIZE; i++) {
    for (j=0; j<SIZE; j++) {
      a[i][j] = i+j;
      b[i][j] = i-j;
    }
  }
			dummyMethod4();
  gettimeofday(&stop, NULL);
  printf("Initialization took: %f seconds\n", diffgettime(start,stop));
  
  gettimeofday(&start, NULL);
  /* matrix-matrix multiply */
			dummyMethod1();
#pragma omp parallel for
  for (i=0; i<SIZE; i++) {  /* for each row */
    for (j=0; j<SIZE; j++) { /* for each column */
      /* initialize result to 0 */
      c[i][j] = 0;

      /* perform dot product */
      for(k=0; k<SIZE; k++) {
	c[i][j] = c[i][j] + a[i][k]*b[k][j];
      }
    }
  }
			dummyMethod2();
  gettimeofday(&stop, NULL);
  printf("Multiplication took: %f seconds\n", diffgettime(start,stop));
  
  /* This is here to make sure the optimizing compiler doesn't
     get any big ideas about "optimizing" code away completely */
  sum=0;
			dummyMethod3();
  for (i=0; i<SIZE; i++) {
    for (j=0; j<SIZE; j++) {
      sum += c[i][j];
    }
  }
			dummyMethod4();
  printf("Sum of elements of c=%f\n", sum);

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