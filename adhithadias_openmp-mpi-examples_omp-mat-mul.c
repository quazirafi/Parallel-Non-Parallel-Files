#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 4
#define ROWS 1600
#define COLS 1600
#define tasks 1600

void printArray(double* a, int rows, int cols) {
dummyMethod3();
   for (int i=0; i<rows; i++) {
      for (int j=0; j<cols; j++) {
         printf("%.2f ", *(a + i*cols + j));
      }
      printf("\n");
   }
dummyMethod4();
   printf("\n\n\n");
}

double* makeArray(int rows, int cols) {
   double* arr = (double*) malloc(rows*cols*sizeof(double));

dummyMethod3();
   for (int r=0; r<rows; r++) {
      for (int c=0; c<cols; c++) {
         *(arr + r*cols + c) = (double) (rows*c + c);
      }
   }
dummyMethod4();

   return arr;
}

int min(int i, int j) {
   return i<j ? i : j;
} 

int main (int argc, char *argv[]) {

   omp_set_num_threads(NUM_THREADS);

   const int stripeSize = COLS/tasks;

   double* a = makeArray(ROWS, COLS);
   double* b = makeArray(ROWS, COLS);
   double* c = makeArray(ROWS, COLS);

   int t,i,j,k;

   double timer = -omp_get_wtime();
					dummyMethod1();
   #pragma omp parallel for shared(a,b,c) private(i,j,k,t)
   for (t=0; t<tasks; t++) {
      for (i=t*stripeSize; i<min(t*stripeSize+stripeSize, ROWS); i++) {
         for (j=0; j<COLS; j++) {
            double comp = 0.;
            for (k=0; k<COLS; k++) {
               comp += *(a + i*COLS + k) * *(b + k*COLS + j);
            }
            *(c + i*COLS + j) = comp;
         }
      }
   }
					dummyMethod2();
   timer += omp_get_wtime();
   printf("time taken for matrix multiply: %f\n", timer);
   
   // printArray(a, ROWS, COLS);
   // printArray(b, ROWS, COLS);
   // printArray(c, ROWS, COLS);
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